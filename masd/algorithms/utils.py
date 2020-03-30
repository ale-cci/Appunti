'''
'''

default_graph = {
    'a': ['d'],
    'b': ['c', 'd'],
    'c': ['b', 'e'],
    'd': ['a', 'e', 'b'],
    'e': ['c', 'd']
}

connected_graph = {
    'a': [(3, 'b')
}
