'''

'''
from collections import defaultdict

default_graph = {
    'a': ['d'],
    'b': ['c', 'd'],
    'c': ['b', 'e'],
    'd': ['a', 'e', 'b'],
    'e': ['c', 'd']
}

connected_graph = {
    'a': [(3, 'b')]
}

def vertices_of(t):
    return 5

def _parse_line(weighted, line):
    if weighted:
        source, dest, weight = line.split(' ')
        weight = int(weight)
    else:
        source, dest = line.split(' ')
        weight = 1

    return source, dest, weight


def adjacency_matrix(graph, biparted=False, weighted=False):
    adj_matrix = {}
    for line in data:
        source, dest, weight = _parse_line(meta, line)

        adj_matrix[(source, dest)] = weight
        if meta['is_biparted']:
            adj_matrix[(dest, source)] = weight

    return adj_matrix


def adjacency_list(graph, biparted=False, weighted=False):
    meta, data = _preprocess_graph(graph)

    adj_list = defaultdict(lambda: [])
    weight = 1
    for line in data:
        source, dest, weight = _parse_line(meta, line)


        adj_list[source].append((dest, weight))
        if meta['is_biparted']:
            adj_list[dest].append((source, weight))
    return dict(adj_list)


def random_graph(nodes=1):
    return '\n'.join([
        '',
        'a d',
        'b c',
        'b d',
        'c b',
        'c e',
        'd a',
        'd e',
        'd b',
        'e c',
        'e d'
    ])

