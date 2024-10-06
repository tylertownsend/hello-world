ORG 0x7c00

; only assemble in 16-bit mode
BITS 16

start:
    mov si, message    ; point to message
    call print
    jmp $              ; infinite loop

print:
    mov bx, 0          ; set video page to 0
.loop:
    lodsb              ; load next byte from SI into AL register then increment SI register
    cmp al, 0          ; check if AL is null
    je .done           ; if null, we are done
    call print_char    ; print character
    jmp .loop          ; repeat
.done:
    ret

print_char:
    mov ah, 0eh        ; teletype output
    int 0x10           ; call BIOS interrupt
    ret

message: db 'Hello world!', 0 ; null-terminated string

; boot signature 55aa on last two bytes of 512-byte boot sector
times  510 - ($ - $$) db 0
dw 0xAA55 ; intel machines are little-endian