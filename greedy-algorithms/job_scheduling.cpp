#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <iomanip>
using namespace std;

struct Process {
    int id;
    int arrival;
    int burst;
    int priority;
    int remaining_time;
    int queue_level;
    int start_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;

    Process(int id, int arrival, int burst, int priority = 0)
        : id(id), arrival(arrival), burst(burst), priority(priority),
          remaining_time(burst), queue_level(0), start_time(-1),
          completion_time(-1), waiting_time(0), turnaround_time(0) {}
};

// Helper function to print results
void printResults(const vector<Process>& processes) {
    cout << "ID  Arrival Burst Priority Start Completion Waiting Turnaround\n";
    for (const auto& p : processes) {
        cout << setw(2) << p.id << " "
             << setw(7) << p.arrival << " "
             << setw(5) << p.burst << " "
             << setw(7) << p.priority << " "
             << setw(5) << p.start_time << " "
             << setw(10) << p.completion_time << " "
             << setw(7) << p.waiting_time << " "
             << setw(10) << p.turnaround_time << "\n";
    }

    float avg_waiting = 0, avg_turnaround = 0;
    for (const auto& p : processes) {
        avg_waiting += p.waiting_time;
        avg_turnaround += p.turnaround_time;
    }
    avg_waiting /= processes.size();
    avg_turnaround /= processes.size();

    cout << "Average Waiting Time: " << avg_waiting << "\n";
    cout << "Average Turnaround Time: " << avg_turnaround << "\n\n";
}

// FCFS Scheduling
void FCFS(vector<Process>& processes) {
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.arrival < b.arrival;
    });

    int current_time = 0;
    for (auto& p : processes) {
        if (current_time < p.arrival) current_time = p.arrival;
        p.start_time = current_time;
        p.completion_time = current_time + p.burst;
        p.turnaround_time = p.completion_time - p.arrival;
        p.waiting_time = p.turnaround_time - p.burst;
        current_time = p.completion_time;
    }
}

// SJF (Non-Preemptive)
void SJF(vector<Process>& processes) {
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.arrival < b.arrival;
    });

    int current_time = 0, n = processes.size();
    vector<bool> completed(n, false);
    int completed_count = 0;

    while (completed_count < n) {
        int idx = -1, min_burst = INT_MAX;
        for (int i = 0; i < n; ++i) {
            if (!completed[i] && processes[i].arrival <= current_time && 
                processes[i].burst < min_burst) {
                min_burst = processes[i].burst;
                idx = i;
            }
        }
        if (idx == -1) { current_time++; continue; }
        
        auto& p = processes[idx];
        p.start_time = current_time;
        p.completion_time = current_time + p.burst;
        p.turnaround_time = p.completion_time - p.arrival;
        p.waiting_time = p.turnaround_time - p.burst;
        current_time = p.completion_time;
        completed[idx] = true;
        completed_count++;
    }
}

// SRTF (Preemptive)
struct CompareRemaining { bool operator()(const Process* a, const Process* b) {
    return a->remaining_time > b->remaining_time; }};

void SRTF(vector<Process>& processes) {
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.arrival < b.arrival; });

    priority_queue<Process*, vector<Process*>, CompareRemaining> pq;
    int current_time = 0, idx = 0;
    Process* current = nullptr;

    while (idx < processes.size() || !pq.empty() || current) {
        while (idx < processes.size() && processes[idx].arrival <= current_time) 
            pq.push(&processes[idx++]);

        if (current && current->remaining_time == 0) {
            current->completion_time = current_time;
            current = nullptr;
        }

        if (!current && !pq.empty()) {
            current = pq.top(); pq.pop();
            if (current->start_time == -1) current->start_time = current_time;
        }

        if (current) {
            current->remaining_time--;
            current_time++;
            if (current->remaining_time == 0) {
                current->completion_time = current_time;
                current->turnaround_time = current->completion_time - current->arrival;
                current->waiting_time = current->turnaround_time - current->burst;
                current = nullptr;
            } else {
                while (idx < processes.size() && processes[idx].arrival <= current_time)
                    pq.push(&processes[idx++]);
                if (!pq.empty() && pq.top()->remaining_time < current->remaining_time) {
                    pq.push(current);
                    current = pq.top();
                    pq.pop();
                }
            }
        } else current_time++;
    }
}

// Priority (Non-Preemptive)
void PriorityNonPreemptive(vector<Process>& processes) {
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.arrival < b.arrival; });

    int current_time = 0, n = processes.size();
    vector<bool> completed(n, false);
    int completed_count = 0;

    while (completed_count < n) {
        int idx = -1, min_priority = INT_MAX;
        for (int i = 0; i < n; ++i) {
            if (!completed[i] && processes[i].arrival <= current_time && 
                processes[i].priority < min_priority) {
                min_priority = processes[i].priority;
                idx = i;
            }
        }
        if (idx == -1) { current_time++; continue; }
        
        auto& p = processes[idx];
        p.start_time = current_time;
        p.completion_time = current_time + p.burst;
        p.turnaround_time = p.completion_time - p.arrival;
        p.waiting_time = p.turnaround_time - p.burst;
        current_time = p.completion_time;
        completed[idx] = true;
        completed_count++;
    }
}

// Priority (Preemptive)
struct ComparePriority { bool operator()(const Process* a, const Process* b) {
    return a->priority > b->priority; }};

void PriorityPreemptive(vector<Process>& processes) {
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.arrival < b.arrival; });

    priority_queue<Process*, vector<Process*>, ComparePriority> pq;
    int current_time = 0, idx = 0;
    Process* current = nullptr;

    while (idx < processes.size() || !pq.empty() || current) {
        while (idx < processes.size() && processes[idx].arrival <= current_time)
            pq.push(&processes[idx++]);

        if (current && current->remaining_time == 0) {
            current->completion_time = current_time;
            current = nullptr;
        }

        if (!current && !pq.empty()) {
            current = pq.top(); pq.pop();
            if (current->start_time == -1) current->start_time = current_time;
        }

        if (current) {
            current->remaining_time--;
            current_time++;
            if (current->remaining_time == 0) {
                current->completion_time = current_time;
                current->turnaround_time = current->completion_time - current->arrival;
                current->waiting_time = current->turnaround_time - current->burst;
                current = nullptr;
            } else {
                while (idx < processes.size() && processes[idx].arrival <= current_time)
                    pq.push(&processes[idx++]);
                if (!pq.empty() && pq.top()->priority < current->priority) {
                    pq.push(current);
                    current = pq.top();
                    pq.pop();
                }
            }
        } else current_time++;
    }
}

// Round Robin
void RoundRobin(vector<Process>& processes, int quantum) {
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.arrival < b.arrival; });

    queue<Process*> q;
    int current_time = 0, idx = 0;

    while (idx < processes.size() || !q.empty()) {
        while (idx < processes.size() && processes[idx].arrival <= current_time)
            q.push(&processes[idx++]);

        if (q.empty()) { 
            current_time = processes[idx].arrival;
            continue;
        }

        Process* p = q.front(); q.pop();
        if (p->start_time == -1) p->start_time = current_time;

        int exec_time = min(quantum, p->remaining_time);
        p->remaining_time -= exec_time;
        current_time += exec_time;

        while (idx < processes.size() && processes[idx].arrival <= current_time)
            q.push(&processes[idx++]);

        if (p->remaining_time > 0) q.push(p);
        else {
            p->completion_time = current_time;
            p->turnaround_time = p->completion_time - p->arrival;
            p->waiting_time = p->turnaround_time - p->burst;
        }
    }
}

// Multilevel Feedback Queue
void MLFQ(vector<Process>& processes) {
    vector<queue<Process*>> queues(3);
    int quantums[] = {8, 16, 0};
    int current_time = 0, idx = 0;

    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.arrival < b.arrival; });

    while (idx < processes.size() || !queues[0].empty() || 
           !queues[1].empty() || !queues[2].empty()) {
        while (idx < processes.size() && processes[idx].arrival <= current_time) {
            processes[idx].remaining_time = processes[idx].burst;
            queues[0].push(&processes[idx++]);
        }

        bool processed = false;
        for (int level = 0; level < 3; ++level) {
            if (!queues[level].empty()) {
                Process* p = queues[level].front();
                queues[level].pop();

                if (p->start_time == -1) p->start_time = current_time;

                int exec_time = quantums[level] ? 
                    min(quantums[level], p->remaining_time) : p->remaining_time;
                p->remaining_time -= exec_time;
                current_time += exec_time;

                while (idx < processes.size() && processes[idx].arrival <= current_time)
                    queues[0].push(&processes[idx++]);

                if (p->remaining_time > 0) {
                    if (level < 2) queues[level+1].push(p);
                    else queues[level].push(p);
                } else {
                    p->completion_time = current_time;
                    p->turnaround_time = p->completion_time - p->arrival;
                    p->waiting_time = p->turnaround_time - p->burst;
                }
                processed = true;
                break;
            }
        }
        if (!processed) current_time = idx < processes.size() ? processes[idx].arrival : current_time;
    }
}

int main() {
    vector<Process> processes = {
        {1, 0, 6, 2},
        {2, 2, 3, 1},
        {3, 4, 2, 3},
        {4, 6, 5, 4},
        {5, 8, 4, 5}
    };

    cout << "FCFS Scheduling:\n";
    vector<Process> fcfs = processes;
    FCFS(fcfs);
    printResults(fcfs);

    cout << "SJF (Non-Preemptive):\n";
    vector<Process> sjf = processes;
    SJF(sjf);
    printResults(sjf);

    cout << "SRTF (Preemptive):\n";
    vector<Process> srtf = processes;
    SRTF(srtf);
    printResults(srtf);

    cout << "Priority Non-Preemptive:\n";
    vector<Process> pnp = processes;
    PriorityNonPreemptive(pnp);
    printResults(pnp);

    cout << "Priority Preemptive:\n";
    vector<Process> pp = processes;
    PriorityPreemptive(pp);
    printResults(pp);

    cout << "Round Robin (Quantum=4):\n";
    vector<Process> rr = processes;
    RoundRobin(rr, 4);
    printResults(rr);

    cout << "Multilevel Feedback Queue:\n";
    vector<Process> mlfq = processes;
    MLFQ(mlfq);
    printResults(mlfq);

    return 0;
}