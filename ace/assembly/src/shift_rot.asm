CPU 8086

SECTION data
number: DB 10010111b

SECTION code
..start:
        mov ax, data
        mov ds, ax

        mov dl, [number]
        call DlRepr         ; dl=10010111b

        mov dl, [number]
        shl dl, 1
        call DlRepr         ; dl=00101110b

        mov dl, [number]
        ror dl, 1
        call DlRepr         ; dl=11001011b

End:    mov ax, 4c00h
        int 21h


; Print binary value of dl
DlRepr: mov cx, 8
        rol dl, 1

        mov ah, 0eh
        xor bx, bx

r_loop: mov al, dl
        and al, 1
        add al, '0'

        int 10h
        rol dl, 1

        loop r_loop

        mov al, 0dh ; Print New line (CR+LF)
        int 10h
        mov al, 0ah
        int 10h

        ror dl, 1   ; Restore dl to orignal value
        ret
