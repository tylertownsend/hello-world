ORG 0x7c00

; only assemble in 16-bit mode
BITS 16

start:
    mov ah, 0eh        ; teletype output
    mov al, 'A'        ; character to print
    int 0x10           ; call BIOS interrupt