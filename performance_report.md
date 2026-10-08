# Performance Analysis Report: Multi-Level CPU Scheduler Simulator

## 1. Introduction

CPU scheduling is an important operating-system function that determines which process receives CPU time. Different scheduling algorithms use different selection strategies, affecting waiting time, turnaround time, and process execution order.

This project implements and compares four CPU scheduling algorithms: First Come, First Served (FCFS), Shortest Job First (SJF), Priority Scheduling, and Round Robin (RR).

## 2. Objectives

* Implement four CPU scheduling algorithms in C++.
* Calculate completion time, turnaround time, and waiting time.
* Compare average waiting time and average turnaround time.
* Understand the behavior and performance of different scheduling strategies.

## 3. Scheduling Algorithms

### 3.1 First Come, First Served (FCFS)

FCFS schedules processes in order of arrival. Once a process begins execution, it continues until completion.

**Characteristics:**

* Simple to implement.
* Non-preemptive.
* Longer processes can increase the waiting time of shorter processes.

### 3.2 Shortest Job First (SJF)

SJF selects the available process with the shortest CPU burst time. This implementation is non-preemptive.

**Characteristics:**

* Can reduce average waiting time.
* Requires knowledge of burst times.
* Longer processes may wait while shorter processes are selected.

### 3.3 Priority Scheduling

Priority Scheduling selects a process based on its assigned priority. The exact priority order depends on the implementation.

**Characteristics:**

* Allows processes to be ranked by importance.
* Non-preemptive in this simulator.
* The priority convention must be consistent when entering process data.

### 3.4 Round Robin (RR)

Round Robin assigns each process a fixed CPU time quantum. If a process does not finish within its quantum, it returns to the ready queue.

**Characteristics:**

* Shares CPU time among ready processes.
* Uses a time quantum to control each execution turn.
* Its performance depends on the selected time quantum.

## 4. Performance Metrics

The simulator evaluates scheduling performance using the following metrics.

**Completion Time (CT)**

The time at which a process finishes execution.

**Turnaround Time (TAT)**

$$
TAT = CT - ArrivalTime
$$

**Waiting Time (WT)**

$$
WT = TAT - BurstTime
$$

**Average Turnaround Time**

$$
Average\ TAT = \frac{\sum TAT}{Number\ of\ Processes}
$$

**Average Waiting Time**

$$
Average\ WT = \frac{\sum WT}{Number\ of\ Processes}
$$

## 5. Experimental Setup

The simulator is implemented in C++ and compiled using the G++ compiler with the C++17 standard.

The same process workload should be used to compare all four algorithms. For Round Robin, the time quantum should be recorded alongside the results. The priority convention used by the implementation should also be documented.

Record the following details for the experiment:

* Number of processes: [Enter value]
* Process workload: [Enter workload]
* Round Robin time quantum: [Enter value]
* Compiler and version: [Enter details]

## 6. Results

Run the simulator using the same workload for each scheduling algorithm and enter the observed values in the table below.

| Algorithm           | Average Waiting Time | Average Turnaround Time |
| ------------------- | -------------------: | ----------------------: |
| FCFS                |       [Enter result] |          [Enter result] |
| SJF                 |       [Enter result] |          [Enter result] |
| Priority Scheduling |       [Enter result] |          [Enter result] |
| Round Robin         |       [Enter result] |          [Enter result] |

*Note: Replace the placeholders with the actual output from your program.*

## 7. Discussion

The performance results can be used to compare how each algorithm handles the same workload.

* **FCFS:** Execution follows arrival order, so a long process can delay processes behind it.
* **SJF:** Selecting the shortest available job can reduce average waiting time for a given workload.
* **Priority Scheduling:** Execution order depends on the assigned priorities and the implementation's priority convention.
* **Round Robin:** Processes receive CPU time in turns, and the time quantum affects scheduling behavior.

The best-performing algorithm for a particular workload can be identified by comparing the measured average waiting time and average turnaround time. The results should be interpreted using the actual workload and simulator output.

## 8. Conclusion

The Multi-Level CPU Scheduler Simulator demonstrates four common CPU scheduling algorithms: FCFS, SJF, Priority Scheduling, and Round Robin.

By calculating completion time, turnaround time, waiting time, and their averages, the project provides a practical way to study and compare scheduling behavior. The experiment results help illustrate how different scheduling strategies affect process execution and waiting time.
