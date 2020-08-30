CPU 8086
;===========================================================[ Documantation ]===
; What are you trying to solve...
;
;
; Variables: Camelcase
; Functions: starts with underscore
; Labels: starts with dot
;
;==============================================================[ Variables ]===
SECTION data
; String1:    resb 100
; String2:    resb 100
; Mask:       db   11110000b

;=============================================================[ EntryPoint ]===
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
        push bx
        call _fun
        add sp, 2*2         ; Restore stack pointer value

        ret


;==============================================================[ Functions ]===

; Function template
; Arg0:
; Arg1:
_fun:
        push bp             ; Store copy of bp
        mov bp, sp          ; Load stack pointer

        mov ax, [bp + 4]    ; Read 2nd arg
        mov ax, [bp + 6]    ; Read 1st arg

        pop bp              ; Restore bp to original state
        ret

