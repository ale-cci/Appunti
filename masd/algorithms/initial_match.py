def available_edges(edges, visited)
    ''' Edges that could be added to the set '''
    return [(i, j) for i, j in edges
            if i not in visited and j not in visited]


def starting_match(V, E):
    L = set()                           # Visited nodes
    M = set()                           # Current match

    edges = available_edges(E - M, L)
    while edges:
        (i, j) = edges.pop()

        L.update([i, j])
        M.add(e)
        edges = available_edges(E - M, L)

    return M
