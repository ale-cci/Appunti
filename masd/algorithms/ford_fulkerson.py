from collections import deque

infinity = 10**20

def ford_fulkerson(adj_list, S, D):
    while True:
        # Passo 1
        label = {
            S: (S, infinity)
        }

        visited = {S}
        frontier = deque([S])
        marked = set()

        while len(visited - marked) > 0:
            # Passo 2
            i = visited.popleft()
            marked.add(i)

            _, delta = label[i]
            for j, product_sended, capacity in adj_list[i]:
                if j in visited:
                    continue

                if product_sended < capacity:
                    # Forward edges
                    label[j] = (i, min(delta, capacity - product_sended))
                else:
                    # Backward edges
                    label[j] = (i, product_sended)

                if j not in visited:
                    visited.add(j)
                    frontier.append(j)

            # Passo 3
            if D in visited:
                _, delta = label[D]

                node = D
                while node != S:
                    update_arc(adj_list, (label[node], node), delta)
                    node, _ = label[node]
                break
        else:
            break

