; Si scriva un programma in Assembly Intel 80x86 che esegua le seguenti operazioni:
; 1. Acquisisca dall’utente mediante tastiera una sequenza di caratteri (carattere per
;    carattere) fino alla pressione del tasto ESC. I caratteri letti devono essere
;    memorizzati in una variabile del segmento dati Stringa (inizializzata con resb
;    256) secondo la convenzione C (cioè la stringa deve essere zero terminata).
; 2. Mediante una funzione ContaSpazi a cui viene passato mediante lo stack come
;    parametro l’indirizzo della variabile Stringa, calcoli il numero di spazi contenuti
;    nella stringa e lo memorizzi nel registro DL.
; 3. Stampi, eventualmente con una funzione, a schermo la stringa memorizzata,
;    stampando un carattere per riga (cioè andando a capo ad ogni carattere) e
;    visualizzandola al contrario (cioè partendo dell’ultimo carattere fino al primo).
CPU 8086

SECTION data
String:         RESB 256

SECTION code
..start:
                mov ax, data
                mov ds, ax
                mov es, ax

                call _main

                mov ax, 4c00h
                int 21h

_main:          mov ah, 01h
                mov di, String

.read_chr:      int 21h
                stosb

                cmp al, 27
                jne .read_chr

                dec di
                mov [di], byte 0

                mov ax, String
                push ax
                call _count_spaces
                add sp, 2

                ret

; [bp + 4] String stored in memory
_count_spaces:  push bp
                mov bp, sp

                xor dl, dl
                xor cx, cx
                mov si, [bp + 4]

.s_loop:        lodsb
                cmp al, ' '
                jne .skip_inc

                inc dl
.skip_inc:      cmp al, 27
                jne .s_loop

                call _print_rev
                pop bp
                ret

; Print reversed string
_print_rev:     std
                mov si, di
                dec si
                cmp si, String
                xor bx, bx
                mov ah, 0eh

.print_chr:     lodsb
                int 10h         ; print character
                mov al, 0ah
                int 10h         ; print CR-LF
                mov al, 0dh
                int 10h

                cmp si, String
                jnl .print_chr

                ret
