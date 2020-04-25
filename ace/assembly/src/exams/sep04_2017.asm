CPU 8086
SECTION data
String1:    RESB 256
String2:    RESB 256
String3:    RESB 512
End1:       DW String1
End2:       DW String2

SECTION code
..start:
            mov ax, data
            mov ds, ax
            mov es, ax

            call _main

            mov ax, 4c00h
            int 21h


_main:      call _read_str

            mov si, String1
            call _print

            mov si, String2
            call _print

            mov bx, String3
            push bx
            mov bx, String1
            push bx
            mov bx, String2
            push bx
            call _join_str
            add sp, 2*3

            mov si, String3
            call _print
            ret


; Read alternated characters in s1, s2
_read_str:  call _load_s1
.read:      mov ax, 0100h
            int 21h             ; Read char to al

            stosb
            cmp al, 27
            je .endloop

            cmp si, String2
            jne .if_str1

.if_str2:   mov [End2], di
            call _load_s1
            jmp .read

.if_str1:   mov [End1], di
            call _load_s2
            jmp .read

.endloop:   ; add terminator character
            mov al, 0
            call _load_s1
            stosb
            call _load_s2
            stosb
            ret



; (s3=8, s1=6, s2=4)
_join_str:  push bp
            mov bp, sp

            mov bx, [bp+4]    ; bx = s2
            mov di, [bp+8]
            xor cx, cx
            dec cx

            ; toggle content in bx
.loop:      cmp bx, [bp+4]
            je .if_js1       ; == s2?

            ; == s1
            mov bx, [bp+4]
            jmp .cont_loop
.if_js1:    ; == s2
            inc cx
            mov bx, [bp+6]
            jmp .cont_loop
.cont_loop:
            mov si, bx
            add si, cx

            mov al, [si]
            cmp al, 's'
            je .loop
            cmp al, 0
            je .end

            stosb
            jmp .loop

.end:       xor al, al  ; Add terminator character
            stosb

            pop bp
            ret


; Utilities
_load_s1:   mov si, String1
            mov di, [End1]
            ret

_load_s2:   mov si, String2
            mov di, [End2]
            ret

; Print string contained in si
_print:     mov ah, 0eh
            xor bx, bx

.loops:     lodsb
            int 10h
            cmp al, 0
            jne .loops

.endp:      mov al, 0dh
            int 10h
            mov al, 0ah
            int 10h
            ret
