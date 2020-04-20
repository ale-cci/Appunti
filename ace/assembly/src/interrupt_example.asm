CPU 8086            ; direttiva per il processore, indica che si
                    ; scrive codice asm 8086 non necessaria

Start:  mov ah, 00h
        int 16h     ; lettura da testiera

        cmp al,1bh  ; check if input == esc
        je Exit

        mov ah, 0eh
        mov bx, 00h ; on page 0
        int 10h     ; Print to video

        jmp Start


Exit:   mov ax, 4C00h
        int 21h     ; Return 0
