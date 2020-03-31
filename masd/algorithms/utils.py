'''
'''

def num_vertices(edges):
    connected = [{lhs, rhs} for weight, lhs, rhs in edges]
    vertices = set().union(*connected)

    return len(vertices)

