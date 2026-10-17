document.addEventListener('DOMContentLoaded', () => {
    const queueContainer = document.getElementById('queue-container');
    // Updated to match the new HTML id
    const statusText = document.getElementById('status-text');
    const enqueueBtn = document.getElementById('enqueue-btn');
    const dequeueBtn = document.getElementById('dequeue-btn');
    const customerInput = document.getElementById('customer-name');

    async function fetchState() {
        const res = await fetch('/api/state');
        const data = await res.json();
        renderQueue(data);
    }

    function renderQueue(state) {
        // Clear previous slots
        queueContainer.innerHTML = '';
        const capacity = state.capacity;
        const slots = state.slots; 
        const front = state.front;
        const rear = state.rear;
        
        // Build each slot div
        for (let i = 0; i < capacity; i++) {
            const slotDiv = document.createElement('div');
            
            if (slots[i] === "") {
                slotDiv.classList.add('empty-slot');
                slotDiv.textContent = '(empty)';
            } else {
                slotDiv.textContent = slots[i];
            }
            
            // Add front pointer with explicit dark theme styling
            if (i === front && front !== -1) {
                const ptr = document.createElement('span');
                ptr.className = 'pointer';
                ptr.textContent = 'Front';
                ptr.style.color = "#10b981"; 
                ptr.style.background = "rgba(16, 185, 129, 0.15)";
                ptr.style.border = "1px solid rgba(16, 185, 129, 0.3)";
                slotDiv.appendChild(ptr);
            }
            
            // Add rear pointer with explicit dark theme styling
            if (i === rear && rear !== -1) {
                const ptr = document.createElement('span');
                ptr.className = 'pointer';
                // Offset higher if front and rear are on the exact same slot
                ptr.style.top = (i === front) ? '-70px' : '-35px'; 
                ptr.textContent = 'Rear';
                ptr.style.color = "#f43f5e";
                ptr.style.background = "rgba(244, 63, 94, 0.15)";
                ptr.style.border = "1px solid rgba(244, 63, 94, 0.3)";
                slotDiv.appendChild(ptr);
            }
            
            queueContainer.appendChild(slotDiv);
        }
        
        // Dynamic Status Math Logic
        if (front === -1) {
            statusText.innerText = "Queue is EMPTY (Front == -1).";
            statusText.style.color = "#38bdf8"; // Neon blue
        } else if ((rear + 1) % capacity === front) {
            statusText.innerText = `Queue is FULL because (Rear: ${rear} + 1) % ${capacity} == Front: ${front}`;
            statusText.style.color = "#f43f5e"; // Neon red
        } else {
            statusText.innerText = `Queue is active. Front: ${front}, Rear: ${rear}`;
            statusText.style.color = "#cbd5e1"; // Default white
        }
    }

    enqueueBtn.addEventListener('click', async () => {
        const name = customerInput.value.trim();
        if (!name) return alert('Enter a customer name');
        const res = await fetch('/api/enqueue', {
            method: 'POST',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify({ customer: name })
        });
        if (!res.ok) {
            const err = await res.text();
            alert('Enqueue failed: ' + err);
        } else {
            const data = await res.json();
            renderQueue(data);
            customerInput.value = '';
        }
    });

    dequeueBtn.addEventListener('click', async () => {
        const res = await fetch('/api/dequeue', { method: 'POST' });
        if (!res.ok) {
            const err = await res.text();
            alert('Dequeue failed: ' + err);
        } else {
            const data = await res.json();
            // Optional: Remove the alert('Served: ...') if you want it to look cleaner
            renderQueue(data.state);
        }
    });

    // Initial load
    fetchState();
});