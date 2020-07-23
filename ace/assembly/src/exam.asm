CPU 8086
; Chiedere iterativamente (fino alla pressione di esc) di inserire
; una cifra numerica (tra 0 e 7) e un singono carattere alfabetico\

; ESC può essere premuto tra stringa e carattere

SECTION data
String1:    RESB 256
String2:    RESB 256
Mask:       DB   01101101b

SECTION text
..start:
            mov ax, data
            mov es, ax
            mov ds, ax


            mov di, String1
            mov si, String2

.start_read:
            ; Read number
            mov ah, 00h
            int 16h


            ; End Read if `esc` is pressed
            cmp al, 27
            je .end_read

            ; Ascii to decimal
            sub al, '0'

            ; Validate number input, check if it's between 0 and 7
            cmp al, 0
            jl .start_read

            cmp al, 7
            ja .start_read

            mov dh, al

            ; Read letter
            mov ah, 00h
            int 16h

            ; End read if `esc` is pressed
            cmp al, 27
            je .end_read

            mov dl, al
            push dx
            call MemorizzaCaratterre
            add sp, 2*1

            jmp .start_read


.end_read:
            mov al, 0
            mov [si], al
            mov [di], al


.end:       mov ax, 4c00h
            int 21h


; Passati mediante stack la cifra e il caratere premuti
; Cifra meno signifiw
MemorizzaCaratterre:
            push bp
            mov bp, sp
            mov bx, [Mask]

            mov ax, [bp+4]


            ; Push to carry flag if the result is 0 or 1
            mov cl, ah
            shr bx, cl

            test bx, 1b

            je .push_v2

.push_v1:   mov [si], al
            inc si
            jmp .end_push

.push_v2:   mov [di], al
            inc di
            jmp .end_push

.end_push:
            test ah, bl

            pop bp
            ret
