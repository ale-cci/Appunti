; Fist assembly program
; Sat 28 Mar 2020 06:58:53 PM CET
;
; Print the next key
SECTION data
Title:  DB  'Type a character (esc to end): .'

; Print title
SECTION text
..start:
start:  mov ax, data    ; load data block
        mov ds, ax      ;
        mov ax, 0       ; initialize 'si' with 0
        mov si, ax

title:  mov al, [Title + si]    ; check for end of string
        cmp al, '.'
        je loop         ; goto loop if string ended

        mov ah, 0eh     ; print current character of the string
        int 10h
        inc si          ; increment and do the same thing
        jmp title       ; with the next character


loop:   mov ax, 0       ; read key from keyboard
        int 16h

        cmp al, 27      ; if key == esc, end the program
        je end

        inc al          ; else increase key ascii code by 1
        mov ah, 0eh
        int 10h         ; and print it

        jmp loop        ; loop forever


end:    mov ax, 4c00h   ; exit with code 0
        int 21h
