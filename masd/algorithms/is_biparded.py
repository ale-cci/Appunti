'''
Check if the current graph is biparted or not
DFS, assigning each vertex the color that differs from the color of its parent
'''
import collections


def is_biparted(graph):
    queue = collections.deque([('a', 0)])
    visited = set()
    color_of = {}

    biparted = True
    while biparted and len(queue):
        parent, color = queue.pop()
        visited.add(parent)
        color_of[parent] = color

        for neightbour in graph[parent]:
            if neightbour not in visited:
                queue.append((neightbour, 1-color))
            elif color_of[neightbour] == color:
                biparted = False

    return biparted


if __name__ == '__main__':
    from utils import default_graph as graph
    print('Is biparted:', is_biparted(graph))

