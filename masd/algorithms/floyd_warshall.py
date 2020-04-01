infty = 10**20

def floyd_warshall(w):
    N = len(w)
    R = [weights[:] for weights in w]
    E = [[None]*N for _ in range(N)]

    for i in range(N):
        for j in range(N):
            if R[i][j] is None:
                R[i][j] = +infty

    for j in range(N):
        for i in set(range(N)) - {j}:
            for k in set(range(N)) - {j}:
                if R[i][k] > R[i][j] + R[j][k]:
                    E[i][k] = j
                    R[i][k] = R[i][j] + R[j][k]

        if any(R[i][i] < 0 for i in range(N)):
            break

    return R, E


if __name__ == '__main__':
    w = [[None,    3,   12,   16],
         [   9, None,   18,    7],
         [   5, None, None,    3],
         [   8, None,    1, None]]

    R, E = floyd_warshall(w)
