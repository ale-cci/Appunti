'''
d_ij = matrice dei costi

per ogni colonna trovo il minimo della colonna

a ogni elemento della colonna sottraggo il minimo (d0)

si ottiene una nuova matrice con pesi >= 0

---

stessa operazione con le righe (d1)

---

ottengo matrice di coefficienti d2

assegnamento rappresentato da matrice X
dove x_ij = 1 se i assegnato a j, 0 else

Nota: sum(x[i][j] for j in V) == 1          # 1 solo nodo assegnato
stesso vale per j

Nota: costo assegnamento = sum(d_ij * x_ij)
= sum(d2 * x_ij) + sum(d1) + sum(d0)


quindi D1 = sum(d1) + D0 = sum(d0) <= sum(d_ij * x_ij) rappresenta
un lower bound del costo

se si trova un matching di costo D1 + D0 allora è ottimo

---
trovare sottinsieme di 0 in d2 di cardinalità max (1 solo x riga e conna)

se insieme ammette soluzione di cardinalità

se delta = n
1h02 dimostraz: siccome gli elementi devono essere indipendenti per
il principio della piccionaia e delta ha cardinalità n, sum_i(x_ij) == 1e sum_j(x_ij) == 1

se delta < n
in caso non si riesca a trovare
va risolto un sottoproblema
'''
def ungherese(d):
    pass

if __name__ == '__main__':
    mtx = [[1, 2, 3],
           [4, 5, 6],
           [7, 8, 9]]
    ungherese(mtx)

