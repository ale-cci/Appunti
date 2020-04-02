; Test program
; Extended error 2: maybe you have forgot .exe
;
; CodeSegment:Offset codice-macchina    istruzione

; u - show disassembled code
; r - shows register {IP: Instruction Pointer,
;                   Bottom right: flags,
;                   }
; d - memory dump
; p - proceed: execute single instruction
start:  mov bx, 0ah
        mov ax, [bx]

end:    mov ax, 4c00h
        int 21h

