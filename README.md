# Customer Service System: Circular Queue Visualization

**Author:** Hafiz Abdullah Shakeel (SAP ID: 72405)  
**Course:** Data Structures and Algorithms (Semester 3)  

## Project Overview
This mini-project demonstrates the implementation of a Circular Queue Abstract Data Type (ADT) in C++. It specifically addresses the "false full" bug found in standard linear queues by utilizing modulo arithmetic to wrap the rear pointer. The C++ backend serves a modern, dark-theme Glassmorphism web frontend via a local HTTP server, allowing for real-time visualization of the queue's state and mathematical conditions.

## Architectural Prompt
This project was built following these core architectural instructions:

> **System Role:** Act as an expert C++ developer and UI/UX engineer. 
> 
> **Project Goal:** Build a "Customer Service System" mini-project that visualizes how a Circular Queue handles customer tickets. 
> 
> **Core Requirements:**
> 1. **Backend (C++):** Implement a robust `CircularQueue` class from scratch using an array. It must include methods for `enqueue()` (add customer), `dequeue()` (serve customer), `isEmpty()`, `isFull()`, and `display()`. 
> 2. **The Logic Fix:** Explicitly address the common bug where a circular queue incorrectly reports as "full." Ensure the `isFull()` condition strictly uses `(rear + 1) % MAX_SIZE == front` and `isEmpty()` checks for `front == -1`. 
> 3. **Frontend/Visualization:** Create a sleek, modern Glassmorphism UI to visualize the queue in real-time. Use a lightweight C++ backend local web server (cpp-httplib) paired with an HTML/CSS/JS frontend. The visualization must clearly show the array slots, the current `front` pointer, the `rear` pointer, and visually demonstrate the wrap-around effect.
> 4. **Educational Output:** Include a dedicated section in the UI that dynamically explains the exact mathematical condition of the queue at that moment (e.g., "Queue is FULL because (Rear: 4 + 1) % Size: 5 == Front: 0").

## Features
* **C++ Backend:** Custom template-based Circular Queue logic.
* **REST API:** Built with `cpp-httplib` and `nlohmann/json` to handle asynchronous GET and POST requests from the client.
* **Dynamic Visualization:** Responsive web UI that dynamically injects HTML elements based on the queue's array state.
* **Educational Math Readout:** Real-time updates displaying the modulo arithmetic proving why the queue is empty, full, or active.
* **Responsive UI:** Word-wrapping for long names, custom Z-indexing for overlapping pointers, and neon glowing effects for active slots.

## Dependencies
This project uses two single-header libraries for the backend server:
* `httplib.h` (cpp-httplib) - For local HTTP server routing.
* `json.hpp` (nlohmann/json) - For C++ to JSON serialization.

## Directory Structure
```text
CustomerServiceSystem/
│
├── build/                      # Compiled executable output
├── src/                        # C++ Source Files
│   ├── CircularQueue.h         # Queue template logic
│   ├── main.cpp                # Server setup and API routes
│   ├── httplib.h               # Web server library
│   └── nlohmann/               
│       └── json.hpp            # JSON library
└── web/                        # Frontend Visualization
    ├── index.html              # UI layout
    ├── style.css               # Glassmorphism dark theme
    └── script.js               # Frontend fetch logic and dynamic rendering