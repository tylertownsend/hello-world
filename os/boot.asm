ORG  0x7c00
BITS 16 ; only assemble in 16-bit mode

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start

_start:
    jmp short start  ; jump to start label
    nop              ; pad out the first sector
    times 33 db 0

start:
    jmp 0:step2; jump to start label

step2:
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ; Start the program by setting the segment registers
    ; We don't want to rely on the BIOS to set up the segment registers
    ; so we set them up ourselves
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    cli                ; disable interrupts ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ; critical section where we don't want to be interrupted
    mov ax, 0x00       ; set up stack space just after the bootloader
    mov ds, ax         ; set DS to the bootloader segment
    mov es, ax         ; set ES to the bootloader segment
    mov ss, ax         ; set SS to the bootloader segment
    mov sp, 0x7c00     ; set SP to 0x7c00
    sti                ; enable interrupts ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

.load_protected:
    cli                   ; disable interrupts ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    lgdt [gdt_descriptor] ; load the GDT
    mov eax, cr0          ; get the current value of CR0
    or eax, 0x1           ; set the protected mode bit
    mov cr0, eax          ; write the new value of CR0
    jmp CODE_SEG:load32   ; jump to the next instruction in 32-bit mode

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; GDT
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
gdt_start:
gdt_null:
    dd 0x0
    dd 0x0

; offset 0x08
gdt_code:        ; code segment descriptor
    dw 0xffff    ; segment limit (bits 0-15)
    dw 0x0       ; base first 0-15 bits
    db 0x0       ; base 16-23 bits
    db 0x9a      ; access byte
    db 11001111b ; high 4 bit flags and the low 4 bit flags
    db 0x0       ; base 24-31 bits

; offset 0x10
gdt_data:        ; code segment descriptor
    dw 0xffff    ; segment limit (bits 0-15)
    dw 0x0       ; base first 0-15 bits
    db 0x0       ; base 16-23 bits
    db 0x92      ; access byte
    db 11001111b ; high 4 bit flags and the low 4 bit flags
    db 0x0       ; base 24-31 bits

gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1 ; size of GDT
    dd gdt_start               ; address of GDT

[BITS 32]
load32:
    mov ax, DATA_SEG
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov ebp, 0x00200000
    mov esp, ebp
    jmp $ ; infinite loop

; boot signature 55aa on last two bytes of 512-byte boot sector
times  510 - ($ - $$) db 0
dw 0xAA55 ; intel machines are little-endian
