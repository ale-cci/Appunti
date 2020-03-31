def dijkstra(adj_matrix: list, source: int):
    N = len(adj_matrix)
    W = {source}
    V = set(range(N))

    dist = [0 if i == source else adj_matrix[source][i]
            for i in range(N)]
    parent = [None if i == source else source
            for i in range(N)]

    while W != V:
        _, x = min((dist[i], i) for i in V - W if dist[i] is not None)
        W.add(x)

        for y in V - W:
            if adj_matrix[x][y] is None:
                continue

            if dist[y] is None or dist[y] > dist[x] + adj_matrix[x][y]:
                parent[y] = x
                dist[y] = dist[x] + adj_matrix[x][y]

    return parent


if __name__ == '__main__':
    w = [[None,    3,   12,   16],
         [   9, None,   18,    7],
         [   5, None, None,    3],
         [   8, None,    1, None]]

    print(dijkstra(w, 0))
