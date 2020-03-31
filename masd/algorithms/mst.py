import utils

graph = [(10, 'A', 'C'), (8, 'A', 'D'), (7, 'D', 'E'),
         (4, 'A', 'E'), (3, 'B', 'A'), (9, 'B', 'D'), (5, 'B', 'E')]
N = utils.vertices_of(graph)

connected = set()
mst = []

edges = sorted(graph)
for edge in edges:
    weight, lhs, rhs = edge

    # Two nodes already connected
    if lhs in connected and rhs in connected:
        continue

    mst.append(edge)
    connected.update({lhs, rhs})

    if len(mst) == N:
        break
