from scheduling import first_come_first_output as fcfo, priority_queue as prio, shortest_job_first, round_robin

#FCFO
assert(fcfo([(24,), (3,), (3,)]) ==  17)
assert(fcfo([(3,), (3,), (24,)]) ==  3)
assert(fcfo([ (10, 2), (29, 3), (3, 4), (7, 5), (12, 1) ]) == 28)

#PRIO
assert(prio([ (10, 2), (29, 3), (3, 4), (7, 5), (12, 1) ]) ==  27.8)

#SJF
assert(shortest_job_first([(24,), (3,), (3,)]) == 3)
assert(shortest_job_first([(10, 2), (29, 3), (3, 4), (7, 5), (12, 1) ]) == 13)

#RR

assert(round_robin([(10, 2), (29, 3), (3, 4), (7, 5), (12, 1) ]) == 23)
assert(round_robin([(12,), (6,), (4,)]) == 12)
