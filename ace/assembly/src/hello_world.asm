CPU 8086

SECTION data
Msg:        DB "Test String",0

SECTION code
..start:
            mov ax, data
            mov ds, ax

            xor bx, bx
            mov ah, 0eh

            mov si, Msg
l_print:    lodsb
            int 10h

            cmp al, 0
            jne l_print

l_end:      mov ax, 4c00h
            int 21h
