import utils

def mst_2(edges, N):
    shortest = [None] * N
    minimum = [None] * N
    # connected = set(range(N))

    for weight, u, v in edges:
        if minimum[u] == None or weight < minimum[u]:
            shortest[u] = (u, v)
            minimum[u] = weight

        if minimum[v] == None or weight < minimum[v]:
            shortest[v] = (u, v)
            minimum[v] = weight

    return set(shortest)

if __name__ == '__main__':
    edges = [(3, 0, 1), ( 5, 0, 2), (9, 0, 3), (20, 0, 4),
             (4, 1, 2), ( 8, 1, 3), (10, 1, 4),
             (7, 2, 3), (11, 2, 4),
             (12, 3, 4)]
    N = utils.num_vertices(edges=edges)

    print(mst_2(edges, N))
