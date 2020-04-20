CPU 8086
; Program to check if the same character is pressed twice

SECTION data ; definisce il segmento dati
UserChr:  RESB   1
IntroMsg: DB     "Press two keys",0ah,0dh,0
SameMsg:  DB     "Same Character inserted twice",0
DiffMsg:  DB     "The Two characters are different",0

SECTION text
..start:    ; definiisce inizio del main
            mov ax, data
            mov ds, ax

            mov si, IntroMsg
            call PrintMsg

            call Read
            mov [UserChr], al

            call Read
            cmp al, [UserChr]
            jne DiffChr

SameChr:    mov si, SameMsg
            call PrintMsg
            jmp End

DiffChr:    mov si, DiffMsg
            call PrintMsg

End:        mov ax, 4c00h
            int 21h


; Read char with int16
Read:       mov ah, 00h
            int 16h
            ret

; Print Message pointed by si
PrintMsg:   mov ah, 0eh
            mov bx, 00h
p_loop:     mov al, [si]
            int 10h

            inc si
            cmp al, 0
            jne p_loop

            ret
