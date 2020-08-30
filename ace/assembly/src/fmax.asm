SECTION data
PascalString db 11,"Test string"
CString db "Replaced xx",0,0,0,0,0
; String2:    resb 100
; Mask:       db   11110000b

SECTION code
..start:
        mov ax, data
        mov ds, ax
        mov es, ax

        call _main

        mov ax, 4c00h       ; Terminate iterrupt
        int 21h

; Program description
_main:
        mov bx, PascalString

        xor cx, cx
        mov cl, [bx]

        push cx
        inc bx

        push bx
        mov ax, CString
        push ax

        call _strcpy
        add sp, 2*3


		mov ax, CString
        push ax             ; Add param to stack
        call _print_c
        add sp, 2*1         ; Restore stack pointer value
.end_main:
        ret



; Print C-Style string passed as first arg
_print_c:
        push bp
        mov bp, sp
        mov si, [bp + 4]

        xor bx, bx
        mov ah, 0eh

.sprint:
        lodsb               ; Load byte to print to al
        test al, al         ; Break print fn if 0 is reached
        jz .eprint
        int 10h
        jmp .sprint

.eprint:
        pop bp
        ret

; Print Pascal string
_print_p:
        push bp
        mov bp, sp

        mov si, [bp+4]
        mov cl, [si]
        inc si

        test cl, cl
        jz .eprint_pascal

        xor bx, bx          ; Prepare print interrupt
        mov ah, 0eh

.sprint_pascal:
        lodsb
        int 10h
        loopz .sprint_pascal

.eprint_pascal:
        pop bp
        ret
