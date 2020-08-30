CPU 8086
; Notation:
; Variables: Camelcase
; Functions: starts with underscore
; Labels: starts with dot
; Take Care

SECTION data
; String1:    resb 100
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


;===================================================================[ Main ]===
_main:
        push ax             ; Add param to stack
        call _fun
        add sp, 2*1         ; Restore stack pointer value

        ret


;==============================================================[ Functions ]===

; Function template
_fun:
        push bp             ; Store copy of bp
        mov bp, sp          ; Load stack pointer

        mov ax, [bp + 4]    ; Read 2nd arg
        mov ax, [bp + 6]    ; Read 1st arg

        pop bp              ; Restore bp to original state
        ret


;==================================================================[ UTILS ]===

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



; Print Pascal-Style string
_print_p:
        push bp
        mov bp, sp

        mov si, [bp]
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



; Read string c-style and print character read
; Arg0 : Max number of char to read
; Arg1 : Where to store the message read
_read_string:
        push bp
        mov bp, sp
        mov di, [bp + 4]
        mov cx, [bp + 6]

        mov ah, 01h

.read_str:
        int 21h             ; Read character from stdin
        cmp al, `\r`        ; Check for terminator character (newline)
        je .terminate_str

        stosb
        loop .read_str

.terminate_str:
        mov al, 0           ; Terminate string C-Style
        stosb

        pop bp
        ret



; Count occurrences of char, result is stored in dx
; Arg0 : Char to search
; Arg1 : C-style string
_in_string:
        push bp
        mov bp, sp

        mov si, [bp + 4]    ; Specify where to read bytes from
        mov bl, [bp + 6]

        xor dx, dx          ; Reset counter
.search_in_string:
        lodsb
        test al, al         ; 0 encountered, terminate loop
        jz .end_char_search

        cmp al, bl          ; Check if current char is a match
        jne .skip_count_increment

        inc dx

.skip_count_increment:
        jmp .search_in_string

.end_char_search:
        pop bp
        ret



; Copy N bytes from a location to another
; Arg0: Number of characters to copy
; Arg1: Source
; Arg2: Destination
_strcpy:
        push bp
        mov bp, sp

        mov di, [bp +4]
        mov si, [bp +6]
        mov cx, [bp +8]

        test cx, cx         ; Base case 0 character to copy
        je .end_strcopy

.start_strcopy:
        lodsb
        stosb
        loop .start_strcopy

.end_strcopy:
        pop bp
        ret



; Copy N bytes from a location to another
; Arg0: Number of characters to copy
; Arg1: Source
; Arg2: Destination
_strcpy:
        push bp
        mov bp, sp

        mov di, [bp +4]
        mov si, [bp +6]
        mov cx, [bp +8]

        test cx, cx         ; Base case 0 character to copy
        je .end_strcopy

.start_strcopy:
        lodsb
        stosb
        loop .start_strcopy

.end_strcopy:
        pop bp
        ret
