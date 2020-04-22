; La funzione CalcVals deve ricevere in ingresso i 4 vettori v1, v2, v3, v4 ed
; N, lunghezza di tali vettori al termine di esecuzione nel registro AX deve
; essere contenuto il numero di volte che il valore V1[i] + V2[N-i-1] e'
; maggiore di V3[N-i-1] + V4[i]
CPU 8086
SECTION data
vect1:      DB   3,  7, -21, 22,   6
vect2:      DB   9,  8,  22,  7,  -9
vect3:      DB  -7, 15,   0, 31, -12
vect4:      DB   5,  9,  -2,  7,  10
N:          DB   5
RES:        DB   0

SECTION code
..start:
            mov ax, data
            mov ds, ax

            call _main

            mov ax, 4c00h
            int 21h


_main:      push bp
            mov bp, sp

            mov dx, vect1
            push dx
            mov dx, vect2
            push dx
            mov dx, vect3
            push dx
            mov dx,  vect4
            push dx

            xor dx,dx
            mov dl, [N]
            push dx

            call _CalcVals
            add sp, 2*5

            pop bp
            ret

; N = +4, v4 = +6, v3=+8, v2=+10, v1=+12
; normal address values (N - cx)
; altered address values (cx -1)
_CalcVals:  push bp
            mov bp, sp

            mov cx, [bp+4]  ; cx = N
            xor ax, ax

            ; For simplification purposes, the assignement equation is viewed
            ; as V1[N - cx] - V4[N - cx] + V2[cx-1] - V3[cx-1]  > 0
.loop:      mov bx, [bp + 12]   ; bx = &vect1
            add bx, [bp + 4]    ; bx = &vect1[N]
            sub bx, cx          ; bx = &vect1[N - cx]
            mov dl, [bx]        ; ax = 1

            mov bx, [bp + 6]    ; vec4
            add bx, [bp + 4]
            sub bx, cx
            sub dl, [bx]

            mov bx, [bp + 8]    ; vec3
            add bx, cx
            dec bx
            sub dl, [bx]

            mov bx, [bp + 10]   ; vec2
            add bx, cx
            dec bx
            add dl, [bx]

            js .noinc           ; skip increment if the result is negative
            inc ax

.noinc:     loop .loop

            pop bp
            ret

