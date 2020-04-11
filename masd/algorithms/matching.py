'''
R           : Nodi analizzati
V_1         : Nodi nella prima partizione
V_2         : Nodi nella seconda partizione
adj_list[N] : nodi adiacenti ad N
M           : Matching
'''
import collections

def biparted_sets(adj_list):
    labels = {}
    pq = collections.deque()

    while free_nodes := adj_list.keys() - labels.keys():
        start = free_nodes.pop()
        labels[start] = True
        pq.append(start)

        while len(pq):
            current = pq.popleft()

            for neightbour in adj_list[current]:
                if not neightbour in pq and not neightbour in labels.keys():
                    labels[neightbour] = not labels[current]
                    pq.append(neightbour)

    v1, v2 = set(), set()
    for key, value in labels.items():
        if value:
            v1.add(key)
        else:
            v2.add(key)
    return v1, v2

def initial_match():
    return set(map(frozenset, [(0, 4), (1, 5)]))

def nodes_in(match):
    return set().union(*match)


def matching_max_cardinality(adj_list):
    V1, V2 = biparted_sets(adj_list)

    M = initial_match()
    L = {}

    while unlabeled := (V1 - L.keys() - nodes_in(M)):
        R = set()
        L = {}

        start = unlabeled.pop()
        L[start] = ('E', '-')

        while available_nodes := L.keys() - R:
            current = available_nodes.pop()
            R.add(current)
            group, parent = L[current]

            if group == 'E':
                valid_neightbours = filter(lambda n: n not in L, adj_list[current])
                for adj_node in valid_neightbours:
                    L[adj_node] = ('O', current)

            else:
                adj_nodes = set(adj_list[current]) - L.keys()
                nodes = {node for node in adj_nodes
                                if frozenset((current, node)) in M}

                if nodes:
                    node = nodes.pop()
                    L[node] = ('E', current)
                else:
                    while L[current][1] != '-':
                        group, next_node = L[current]
                        if group == 'O':
                            M.add(frozenset((current, next_node)))
                        else:
                            M.remove(frozenset((current, next_node)))

                        current = next_node
                    break

    return M



if __name__ == '__main__':
    adj_list = {
        0: [4],
        1: [5, 6, 7],
        2: [5],
        3: [4],
        4: [0, 3],
        5: [1, 2],
        6: [1],
        7: [1]
    }

    matching = matching_max_cardinality(adj_list)
    print(matching)

