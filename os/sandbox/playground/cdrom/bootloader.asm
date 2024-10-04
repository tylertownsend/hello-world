;************************************************
;       Boot.asm
;
;
;***********************************************
bits 16                   ; We are still in 16 bit real mode
org 0x7C00                ; The standard loading address for boot sectors

start:
    ; Initialize registers and segments
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov sp, 0x7C00       ; Stack pointer setup at the start of the boot sector

    ; Print a message (For example purposes, uses BIOS interrupt)
print_char:
    lodsb                ; Load string byte at SI into AL
    or al, al            ; Test if AL is zero (end of string)
    jz halt              ; If zero, jump to halt
    mov ah, 0x0E         ; BIOS teletype output
    int 0x10             ; BIOS interrupt to print character in AL
    jmp print_char       ; Jump back to print the next character

halt:
    cli                  ; Disable interrupts
    hlt                  ; Halt the system

; The standard PC boot signature
times 510 - ($ - $$) db 0 ; Pad the remainder of the boot sector with zeros
dw 0xAA55   