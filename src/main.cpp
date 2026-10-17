#define _WIN32_WINNT 0x0A00
#include "CircularQueue.h"
#include "httplib.h"
#include "nlohmann/json.hpp"
#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;
using json = nlohmann::json;

int main() {
    // Configuration
    const int QUEUE_CAPACITY = 5;
    CircularQueue queue(QUEUE_CAPACITY);

    // Create HTTP server (listening on localhost:8080)
    httplib::Server svr;

    // Serve static files (HTML/CSS/JS) from the "web" directory.
    std::string web_root = "web"; // relative to current working directory (project root)
    if (!fs::exists(web_root)) {
        std::cerr << "Web directory not found: " << web_root << std::endl;
        return 1;
    }
    svr.set_mount_point("/", web_root.c_str());

    // Helper to build queue state JSON.
    auto queue_state = [&]() {
        json j;
        j["capacity"] = queue.capacity();
        j["front"] = queue.frontIndex();
        j["rear"] = queue.rearIndex();
        j["isEmpty"] = queue.isEmpty();
        j["isFull"] = queue.isFull();
        j["slots"] = queue.display();
        // Human‑readable explanation of current condition.
        if (queue.isFull()) {
            j["explanation"] = "Queue is FULL because (Rear: " + std::to_string(queue.rearIndex()) + " + 1) % Size: " + std::to_string(queue.capacity()) + " == Front: " + std::to_string(queue.frontIndex());
        } else if (queue.isEmpty()) {
            j["explanation"] = "Queue is EMPTY because front == -1.";
        } else {
            j["explanation"] = "Queue is NEITHER full nor empty.";
        }
        return j.dump();
    };

    // Endpoint to fetch current queue state.
    svr.Get("/api/state", [&](const httplib::Request&, httplib::Response& res) {
        res.set_content(queue_state(), "application/json");
    });

    // Enqueue endpoint (expects JSON {"customer": "Name"})
    svr.Post("/api/enqueue", [&](const httplib::Request& req, httplib::Response& res) {
        try {
            auto j = json::parse(req.body);
            std::string customer = j.value("customer", "");
            if (customer.empty()) {
                res.status = 400;
                res.set_content("{\"error\": \"Missing customer name\"}", "application/json");
                return;
            }
            if (!queue.enqueue(customer)) {
                res.status = 409; // Conflict – queue full
                res.set_content("{\"error\": \"Queue is full\"}", "application/json");
                return;
            }
            res.set_content(queue_state(), "application/json");
        } catch (const std::exception& e) {
            res.status = 400;
            res.set_content(std::string("{\"error\": \"" ) + e.what() + "}" , "application/json");
        }
    });

    // Dequeue endpoint – removes the front element.
    svr.Post("/api/dequeue", [&](const httplib::Request&, httplib::Response& res) {
        if (queue.isEmpty()) {
            res.status = 409; // Conflict – queue empty
            res.set_content("{\"error\": \"Queue is empty\"}", "application/json");
            return;
        }
        std::string served = queue.dequeue();
        json j;
        j["served"] = served;
        // Return updated state as well.
        j["state"] = json::parse(queue_state());
        res.set_content(j.dump(), "application/json");
    });

    std::cout << "Server listening on http://localhost:8080" << std::endl;
    svr.listen("0.0.0.0", 8080);
    return 0;
}
