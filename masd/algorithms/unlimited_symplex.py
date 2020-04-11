#TODO
import utils
from copy import copy
from collections import defaultdict

def is_optimal(rcc_list):
    return all(rcc >= 0 for rcc, edge in rcc_list)

def find_cycle(tree, edge):
    # graph is considered bidirectional
    return set()

def calculate_rcc(cycle):
    pass

def step_1(b: list, adjacency_list):
    assert(sum(b) == 0)
    graph = copy(adjacency_list)
    N = len(graph.keys())

    q = N
    base = set()
    for i, value in enumerate(b):
        if value < 0:
            graph[q].add((1, i))
            base.add((q, i))

        else:
            graph[i].add((1, q))
            base.add((i, q))
    b += [0]


    # reduced cost coefficient list
    rccs = {}
    for nodeA, neightbours in graph:
        for nodeB in neightbours:
            if (nodeA, nodeB) in base:
                continue

            cycle = find_cycle(graph, edge)
            rcc = calculate_rcc(cycle)

            rccs[(nodeA, nodeB)] = rcc


    while not is_optimal(rcc_list):
        # Operazione di cambiamento di base
        # Aggiornamento ccr

    if costo(base, costi) > 0:
        raise Exception('Non esiste soluzione')

    # Tolgo collegamento a q dalla base
    return base


if __name__ == '__main__':
    b = [1, 3, -4]
    edges = [()]

    adjacency_list = defaultdict(lambda: [])
    for (cost, u, v) in edges:
        adjacency_list[u].add((cost, v))

    step_1(b, adjacency_list)
