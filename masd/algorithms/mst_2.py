import utils

def mst_2(edges):
    N = utils.num_vertices(edges=edges)
    mst = set()
    component = list(range(N))

    while len(set(component)) > 1:
        minimum = {set_name: None for set_name in set(component)}
        shortest = {set_name: None for set_name in set(component)}

        for weight, u, v in edges:
            s_u = component[u]
            s_v = component[v]

            if s_u == s_v:
                continue

            if minimum[s_u] is None or weight < minimum[s_u]:
                shortest[s_u] = (u, v)
                minimum[s_u] = weight

            if minimum[s_v] is None or weight < minimum[s_v]:
                shortest[s_v] = (u, v)
                minimum[s_v] = weight

        mst.update(shortest.values())

        # Find connected components with union-disjoint set
        for u, v in shortest.values():
            utils.union_set(component, u, v)
        component = [utils.get_set(component, i) for i in component]

    return mst


if __name__ == '__main__':
    edges = [(1, 0, 1), (2, 0, 2), (4, 0, 3), (3, 1, 2), (4, 1, 3), (1, 2, 3)]
    N = utils.num_vertices(edges=edges)

    print(mst_2(edges))
