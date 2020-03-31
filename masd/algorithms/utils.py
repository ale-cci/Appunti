'''
'''

def num_vertices(edges):
    connected = [{lhs, rhs} for weight, lhs, rhs in edges]
    vertices = set().union(*connected)

    return len(vertices)


def edges_list(adj_matrix):
    return [(adj_matrix[x][y], x, y)
            for x in range(0, len(adj_matrix))
            for y in range(x+1, len(adj_matrix))]


def get_set(component, u):
    if component[u] == u:
        return u

    component[u] = get_set(component, component[u])
    return component[u]


def union_set(component, u, v):
    component[get_set(component, u)] = get_set(component, v)

