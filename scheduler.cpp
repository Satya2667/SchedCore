
#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
#include <algorithm>
#include <fstream>
#include <string>
#include <climits>
#include <cstdlib>

using namespace std;

// ----------------------
// Constants
// ----------------------
const int TIME_QUANTUM = 4;

// ----------------------
// Job structure
// ----------------------
struct Job {
    string id;
    int arrival;
    int burst;
    int priority;
    int waitingTime;
    int turnaroundTime;
};

// ----------------------
// Calculate turnaround times
// Turnaround Time = Waiting Time + Burst Time
// ----------------------
void calculateTurnaroundTimes(vector<Job> &jobs) {
    for (auto &job : jobs) {
        job.turnaroundTime = job.waitingTime + job.burst;
    }
}

// ----------------------
// First-Come-First-Serve (FCFS)
// ----------------------
vector<Job> fcfs(vector<Job> jobs) {
    stable_sort(jobs.begin(), jobs.end(),
        [](const Job &a, const Job &b) {
            return a.arrival < b.arrival;
        });

    int currentTime = 0;

    for (auto &job : jobs) {
        if (currentTime < job.arrival) {
            currentTime = job.arrival;
        }

        job.waitingTime = currentTime - job.arrival;
        currentTime += job.burst;
    }

    calculateTurnaroundTimes(jobs);
    return jobs;
}

// ----------------------
// Shortest Job First (Non-preemptive)
// Shortest available burst time is selected.
// ----------------------
vector<Job> sjf(vector<Job> jobs) {
    int n = static_cast<int>(jobs.size());

    vector<Job> scheduledJobs;
    vector<bool> finished(n, false);

    int currentTime = 0;
    int completedJobs = 0;

    while (completedJobs < n) {
        int idx = -1;

        // Select the available job with the shortest burst.
        // Ties are resolved by earlier arrival time.
        // If both tie, original input order is retained.
        for (int i = 0; i < n; i++) {
            if (!finished[i] && jobs[i].arrival <= currentTime) {
                if (idx == -1 ||
                    jobs[i].burst < jobs[idx].burst ||
                    (jobs[i].burst == jobs[idx].burst &&
                     jobs[i].arrival < jobs[idx].arrival)) {
                    idx = i;
                }
            }
        }

        // If no job has arrived, jump to the next arrival time.
        if (idx == -1) {
            int nextArrival = INT_MAX;

            for (int i = 0; i < n; i++) {
                if (!finished[i]) {
                    nextArrival = min(nextArrival, jobs[i].arrival);
                }
            }

            currentTime = nextArrival;
            continue;
        }

        jobs[idx].waitingTime = currentTime - jobs[idx].arrival;
        currentTime += jobs[idx].burst;

        finished[idx] = true;
        scheduledJobs.push_back(jobs[idx]);
        completedJobs++;
    }

    calculateTurnaroundTimes(scheduledJobs);
    return scheduledJobs;
}

// ----------------------
// Priority Scheduling (Non-preemptive)
// Lower priority number = higher priority.
// ----------------------
vector<Job> priorityScheduling(vector<Job> jobs) {
    stable_sort(jobs.begin(), jobs.end(),
        [](const Job &a, const Job &b) {
            return a.arrival < b.arrival;
        });

    int n = static_cast<int>(jobs.size());
    int currentTime = 0;

    vector<Job> scheduledJobs;
    vector<bool> finished(n, false);
    int completedJobs = 0;

    while (completedJobs < n) {
        int idx = -1;
        int highestPriority = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (!finished[i] && jobs[i].arrival <= currentTime) {
                if (idx == -1 || jobs[i].priority < highestPriority) {
                    highestPriority = jobs[i].priority;
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            int nextArrival = INT_MAX;

            for (int i = 0; i < n; i++) {
                if (!finished[i]) {
                    nextArrival = min(nextArrival, jobs[i].arrival);
                }
            }

            currentTime = nextArrival;
            continue;
        }

        jobs[idx].waitingTime = currentTime - jobs[idx].arrival;
        currentTime += jobs[idx].burst;

        finished[idx] = true;
        scheduledJobs.push_back(jobs[idx]);
        completedJobs++;
    }

    calculateTurnaroundTimes(scheduledJobs);
    return scheduledJobs;
}

// ----------------------
// Round Robin Scheduling
// ----------------------
vector<Job> roundRobin(vector<Job> jobs, int quantum) {
    if (quantum <= 0) {
        cerr << "[ERROR] Time quantum must be positive.\n";
        return {};
    }

    // Sort by arrival time; stable sort preserves input order for ties.
    stable_sort(jobs.begin(), jobs.end(),
        [](const Job &a, const Job &b) {
            return a.arrival < b.arrival;
        });

    int n = static_cast<int>(jobs.size());
    vector<int> remainingBurst(n);

    for (int i = 0; i < n; i++) {
        remainingBurst[i] = jobs[i].burst;
    }

    queue<int> readyQueue;
    int currentTime = 0;
    int nextJob = 0;
    int completedJobs = 0;

    while (completedJobs < n) {
        // If the queue is empty, move to the next arriving job.
        if (readyQueue.empty()) {
            if (nextJob < n && currentTime < jobs[nextJob].arrival) {
                currentTime = jobs[nextJob].arrival;
            }

            while (nextJob < n &&
                   jobs[nextJob].arrival <= currentTime) {
                readyQueue.push(nextJob);
                nextJob++;
            }

            if (readyQueue.empty()) {
                continue;
            }
        }

        int idx = readyQueue.front();
        readyQueue.pop();

        int execTime = min(quantum, remainingBurst[idx]);

        currentTime += execTime;
        remainingBurst[idx] -= execTime;

        // Add jobs that arrived during this time slice.
        while (nextJob < n &&
               jobs[nextJob].arrival <= currentTime) {
            readyQueue.push(nextJob);
            nextJob++;
        }

        if (remainingBurst[idx] > 0) {
            // This job still needs CPU time.
            readyQueue.push(idx);
        } else {
            jobs[idx].turnaroundTime =
                currentTime - jobs[idx].arrival;

            jobs[idx].waitingTime =
                jobs[idx].turnaroundTime - jobs[idx].burst;

            completedJobs++;
        }
    }

    return jobs;
}

// ----------------------
// Display and log results
// ----------------------
void displayAndLogResults(
    const string &algoName,
    const vector<Job> &jobs,
    ofstream &logFile
) {
    cout << "\n=== " << algoName << " ===\n";
    logFile << "\n=== " << algoName << " ===\n";

    cout << left << setw(12) << "Process"
         << setw(10) << "Arrival"
         << setw(10) << "Burst"
         << setw(10) << "Priority"
         << setw(15) << "Waiting Time"
         << setw(20) << "Turnaround Time" << '\n';

    logFile << left << setw(12) << "Process"
            << setw(10) << "Arrival"
            << setw(10) << "Burst"
            << setw(10) << "Priority"
            << setw(15) << "Waiting Time"
            << setw(20) << "Turnaround Time" << '\n';

    double totalWaitingTime = 0;
    double totalTurnaroundTime = 0;

    for (const auto &job : jobs) {
        cout << left << setw(12) << job.id
             << setw(10) << job.arrival
             << setw(10) << job.burst
             << setw(10) << job.priority
             << setw(15) << job.waitingTime
             << setw(20) << job.turnaroundTime << '\n';

        logFile << left << setw(12) << job.id
                << setw(10) << job.arrival
                << setw(10) << job.burst
                << setw(10) << job.priority
                << setw(15) << job.waitingTime
                << setw(20) << job.turnaroundTime << '\n';

        totalWaitingTime += job.waitingTime;
        totalTurnaroundTime += job.turnaroundTime;
    }

    if (!jobs.empty()) {
        double avgWaitingTime = totalWaitingTime / jobs.size();
        double avgTurnaroundTime =
            totalTurnaroundTime / jobs.size();

        cout << fixed << setprecision(2);
        logFile << fixed << setprecision(2);

        cout << "Average Waiting Time: "
             << avgWaitingTime << '\n';
        cout << "Average Turnaround Time: "
             << avgTurnaroundTime << '\n';

        logFile << "Average Waiting Time: "
                << avgWaitingTime << '\n';
        logFile << "Average Turnaround Time: "
                << avgTurnaroundTime << '\n';
    }
}

// ----------------------
// Main function
// ----------------------
int main() {
    // Create logs directory.
#ifdef _WIN32
    system("mkdir logs >nul 2>nul");
#else
    system("mkdir -p logs");
#endif

    // Open input file.
    ifstream inFile("data/input_jobs.txt");

    if (!inFile) {
        cerr << "[ERROR] Could not open data/input_jobs.txt\n";
        return 1;
    }

    vector<Job> jobs;
    string id;
    int arrival, burst, priority;

    // Read and validate input.
    while (inFile >> id >> arrival >> burst >> priority) {
        if (arrival < 0 || burst <= 0) {
            cerr << "[ERROR] Invalid job: " << id
                 << ". Arrival must be >= 0 and burst must be > 0.\n";
            return 1;
        }

        jobs.push_back({
            id, arrival, burst, priority, 0, 0
        });
    }

    if (!inFile.eof()) {
        cerr << "[ERROR] Invalid input format in data/input_jobs.txt\n";
        return 1;
    }

    inFile.close();

    if (jobs.empty()) {
        cerr << "[ERROR] No jobs found in input_jobs.txt\n";
        return 1;
    }

    // Open output log.
    ofstream logFile("logs/results.log");

    if (!logFile) {
        cerr << "[ERROR] Could not open logs/results.log for writing.\n";
        return 1;
    }

    logFile << "CPU Scheduler Simulation Log\n";

    // Run FCFS.
    auto fcfsJobs = fcfs(jobs);
    displayAndLogResults(
        "First-Come-First-Serve (FCFS)",
        fcfsJobs,
        logFile
    );

    // Run SJF.
    auto sjfJobs = sjf(jobs);
    displayAndLogResults(
        "Shortest Job First (Non-preemptive)",
        sjfJobs,
        logFile
    );

    // Run Priority Scheduling.
    auto priorityJobs = priorityScheduling(jobs);
    displayAndLogResults(
        "Priority Scheduling (Non-preemptive)",
        priorityJobs,
        logFile
    );

    // Run Round Robin.
    auto rrJobs = roundRobin(jobs, TIME_QUANTUM);
    displayAndLogResults(
        "Round Robin (Quantum = " +
            to_string(TIME_QUANTUM) + ")",
        rrJobs,
        logFile
    );

    logFile << "\nSimulation completed successfully.\n";
    logFile.close();

    cout << "\n[INFO] Scheduler simulation completed successfully.\n";
    cout << "[INFO] Check logs/results.log for detailed output.\n";

    return 0;
}
