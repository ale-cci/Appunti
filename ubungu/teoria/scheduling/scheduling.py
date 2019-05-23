#!/usr/bin/env python3
from itertools import cycle, dropwhile

def first_come_first_output(processes: list):
    time, total_time = 0, 0

    for p in processes:
        total_time += time
        time += p[0]

    return total_time / len(processes)


def shortest_job_first(processes: list):
    return first_come_first_output(sorted(processes))

def priority_queue(processes: list):
    return first_come_first_output(sorted(processes, key=lambda x: x[1]))

def round_robin(processes: list):
    TIME_SLICE = 10

    execution_times = list(map(lambda p: p[0], processes))
    total_time      = -sum(execution_times)
    time = 0

    while execution_times:
        for proc_time in execution_times:
            time += min(proc_time, TIME_SLICE)
            if proc_time <= TIME_SLICE:
                total_time += time

        execution_times = list(map(lambda p: p-TIME_SLICE, execution_times))
        execution_times = list(filter(lambda p: p>0, execution_times))

    return total_time / len(processes)

if __name__ == "__main__":
    print("[", "="*30, "> SCHEDULING SIMULATOR <", "="*30, "]\n", sep="")
    print(" Type in processes execution time and (default: 128) priority; write end top stop")

    processes = []
    while 1:
        proc = input(" Insert current process time and priority: ").strip() or "0"
        if proc == "end":
            break

        proc = proc.split(" ")
        processes.append((int(proc[0]), int(proc[1]) if len(proc) > 1 else 128))

    assert processes, "At least one process needed"
    print("\n Shortest Job First:     ", shortest_job_first(processes))
    print(" First come First Output:", first_come_first_output(processes))
    print(" Priority Queue:         ", priority_queue(processes))
    print(" Round Robin:            ", round_robin(processes))


