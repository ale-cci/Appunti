; 1h:44m
; Calcolare la somma degli indici, calcolare anche quanti valori di indice sono sbagliati (fuori dai limiti del vettore)

; Indicare a video il numero di indici sbagliati tramite funzione NumeriSbagliati (parametri per stack)
; La funzione deve scrivere a schermo String, seguito dal numero passato come parametro

; Riportare a video il valore della somma, supponendo che contenga al massimo 3 cifre
CPU 8086

SECTION data
; Vett 8b |N| di valori sia positivi che negativi
; Vett2 di |N2| byte di indici positivi

Vett: db 12, -10, 101, -55, -64, 118, 8, 44, 97, -22
N: db 10
Indici: db 2, 0, 10, 3, 1, 22, 1, 7, 8, 4
N2: db 10
String: DB 'Numero di indici sbagliati = ',0
NewLine: DB 0ah,0dh,0
MsgTotal: DB 'Totale complessivo = ',0
Total: DW 0,0

SECTION code
..start:
            mov ax, data
            mov ds, ax
            mov es, ax

            call _main

            mov ax, 4c00h
            int 21h

_main:      mov ax, Vett
            push ax
            xor ah, ah
            mov al, [N]
            push ax
            mov ax, Indici
            push ax
            xor ah, ah
            mov al, [N2]
            push ax
            call _calc_sum
            add sp, 2*4


            mov si, MsgTotal
            call _print_string

            mov ax, [Total]
            push ax
            call _print_no
            add sp, 2

            mov si, NewLine
            call _print_string
            ret


; N2 = 4, Indici = 6, N = 8, Vett = 10
_calc_sum:  push bp
            mov bp, sp
            xor dx, dx        ; Error register

            mov cx, [bp + 4]
.loops:     mov bx, [bp + 6]
            sub bx, cx
            add bx, [bp + 4]  ; bx = Indici + i

            mov al, [bp + 8]  ; ax = N
            mov bl, [bx]      ; bx = *(Indici + i)
            cmp bl, al
            jnge .ok

            inc dx
            loop .loops

.ok:        mov ax, [Total]
            xor bh, bh
            add bl, [bp +10]  ; bx = Vett[*(Indici +i)]
            add al, [bx]
            mov [Total], ax

            loop .loops

            push dx
            call _wrong_nums
            add sp, 2

            pop bp
            ret


; Print parameter passed
_print_no:  push bp
            mov bp, sp
            mov cx, [bp + 4]

            ; If negative print minus
            test cx, cx
            jns .no_sign
            mov al, '-'
            xor bx, bx
            mov ah, 0eh
            int 10h

            neg cx
.no_sign:
            ; Parse cx, content
            ; if more than 1 cyphre put shifted value to stack and call function
            ; else print cyphre and quit

            cmp cx, 10
            jl .just_print

            mov ax, cx
            mov bx, 10
            xor dx, dx
            div bx

            push dx ; Reminder
            push ax ; Result
            call _print_no
            add sp, 2
            pop ax

.just_print: xor bx, bx
            mov ah, 0eh
            add al, '0'
            int 10h

            pop bp
            ret

_print_string: xor bx, bx
            mov ah, 0eh
.sprint:    lodsb
            test al, al
            jz .eprint
            int 10h
            jmp .sprint
.eprint:    ret


; Wrong numbers [bp +4]
_wrong_nums: push bp
            mov bp, sp

            ; Print message
            mov si, String
            call _print_string

            ; Print number
            mov ax, [bp + 4]
            push ax
            call _print_no
            add sp, 2

            ; Pring new line
            mov si, NewLine
            call _print_string

            pop bp
            ret
