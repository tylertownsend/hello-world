[BITS 32]
global _start

CODE_SEQ equ 0x08
DATA_SEG equ 0x10

_start:
    mov ax, DATA_SEG
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov ebp, 0x00200000
    mov esp, ebp

    ;--------------------------------------------------------------------------
    ; enable the A20 line
    ;--------------------------------------------------------------------------
    ; 
    in al, 0x92  ; Reads the value from the I/O port 0x92 into the al register
    or al, 2     ; Set second bit of al register (A20 enablement bit)
    out 0x92, al ; Writes modified balue back to I/O port 0x92

    jmp $ ; infinite loop
