infinity = 10**20

def ford_fulkerson(adj_list, S, D):
    while True:
        # Passo 1
        L[S] = (S, infinity)
        E = {S}
        R = set()

        while len(E - R) > 0:
            # Passo 2
            i = (E - R).pop()

            _, delta = L[i]
            for j, product_sended, capacity in adj_list[i]:
                if j in E:
                    continue

                if product_sended < capacity:
                    # Forward edges
                    L[j] = (i, min(delta, capacity - product_sended))
                else:
                    # Backward edges
                    L[j] = (i, product_sended)

                E.add(j)
            R.add(i)

            # Passo 3
            if D in E:
                _, delta = L[D]

                node = D
                while node != S:
                    update_arc(adj_list, (L[node], node), delta)
                    node, _ = L[node]
                break
        else:
            break

