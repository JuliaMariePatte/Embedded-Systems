# Real-Time Task Scheduling Optimizer

## Project Overview
This repository contains a C++ implementation for non-preemptive scheduling of periodic tasks in real-time embedded systems. 
The project focuses on verifying task schedulability and generating optimal execution schedules that minimize total waiting time while ensuring all deadlines are met.

## Features
- CPU utilization analysis to determine task set schedulability
- Exhaustive search algorithm to find optimal non-preemptive job scheduling

## Implementation Details
The algorithm computes the hyperperiod (LCM of all task periods) and evaluates all possible execution permutations to find the sequence with minimum waiting time. 
The current implementation successfully handles 3-4 tasks, demonstrating the trade-off between optimality and computational complexity in real-time scheduling.

## Limitations & Future Work
While the exhaustive search guarantees optimal results for small task sets, its factorial complexity prevents scaling to larger systems. 
Future improvements could incorporate heuristic approaches or algorithms like Earliest Deadline First (EDF) to handle more complex task sets with acceptable computational overhead.

## Academic Context
This project was developed as part of the Real-Time Embedded Systems course at IPSA Toulouse, exploring fundamental concepts in task scheduling theory and practical implementation challenges.
