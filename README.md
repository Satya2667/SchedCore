# Multi-Level CPU Scheduler Simulator

## Overview

The Multi-Level CPU Scheduler Simulator is a C++ project that demonstrates and compares different CPU scheduling algorithms. It simulates how processes are scheduled for CPU execution and calculates performance metrics for each algorithm.

## Scheduling Algorithms

The simulator supports the following algorithms:

1. **First Come, First Served (FCFS)** — Processes are executed in order of arrival.
2. **Shortest Job First (SJF)** — The process with the shortest burst time is selected next. This implementation is non-preemptive.
3. **Priority Scheduling** — Processes are scheduled according to their priority. This implementation is non-preemptive.
4. **Round Robin (RR)** — Each process receives a fixed time quantum, allowing processes to share CPU time fairly.

## Performance Metrics

The simulator calculates the following metrics:

* **Completion Time (CT):** The time at which a process finishes execution.
* **Turnaround Time (TAT):** The total time taken from arrival to completion.
* **Waiting Time (WT):** The total time a process spends waiting in the ready queue.
* **Average Turnaround Time:** The average turnaround time of all processes.
* **Average Waiting Time:** The average waiting time of all processes.

## Technologies Used

* C++
* Standard Template Library (STL)
* Visual Studio Code
* MinGW GCC/G++ compiler

## How to Compile and Run

### Requirements

* A C++ compiler, such as MinGW G++
* Visual Studio Code (optional)

### Compile

Open a terminal in the project directory and run:

```bash
g++ -std=c++17 -Wall -Wextra scheduler.cpp -o scheduler.exe
```

### Run

On Windows PowerShell:

```powershell
.\scheduler.exe
```

## Input Format

Enter the process information using the format required by the program:

```text
PID ArrivalTime BurstTime Priority
```

Example:

```text
P1 0 5 2
P2 1 3 1
P3 2 8 3
P4 3 6 2
```

The exact input format depends on how input is handled in `scheduler.cpp`.

## Project Structure

```text
Multi-Level_CPU_Scheduler_Simulator/
├── scheduler.cpp
├── README.md
├── PERFORMANCE_REPORT.md
└── .vscode/
    └── tasks.json
```

## Project Objectives

* Implement multiple CPU scheduling algorithms.
* Compare scheduling performance using calculated metrics.
* Understand the differences between FCFS, SJF, Priority Scheduling, and Round Robin.
* Demonstrate CPU scheduling concepts through a C++ simulation.

## License

This project is intended for educational purposes.
"# SchedCore" 
