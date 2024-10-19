ORG  0
BITS 16 ; only assemble in 16-bit mode

_start:
    jmp short start  ; jump to start label
    nop              ; pad out the first sector
    times 33 db 0

start:
    jmp 0x7c0:step2; jump to start label

step2:
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ; Start the program by setting the segment registers
    ; We don't want to rely on the BIOS to set up the segment registers
    ; so we set them up ourselves
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    cli                ; disable interrupts ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ; critical section where we don't want to be interrupted
    mov ax, 0x7c0      ; set up stack space just after the bootloader
    mov ds, ax         ; set DS to the bootloader segment
    mov es, ax         ; set ES to the bootloader segment

    mov ax, 0x00       ; set up stack pointer
    mov ss, ax         ; set SS to the bootloader segment
    mov sp, 0x7c00     ; set SP to 0x7c00
    sti                ; enable interrupts ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    mov ah, 2 ; READ SECTOR COMMAND
    mov al, 1 ; NUMBER OF SECTORS TO READ
    mov ch, 0 ; Cyclinder low eight bits
    mov cl, 2 ; Read sector two
    mov dh, 0 ; Head number
    mov bx, buffer ; Buffer to read to
    int 0x13 ; BIOS DISK INTERRUPT
    jc error ; Jump to error if carry flag is set

    mov si, buffer
    call print

    jmp $              ; infinite loop

  error:
    mov si, error_message
    call print
    jmp $

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
error_message: db 'Error reading disk', 0

; boot signature 55aa on last two bytes of 512-byte boot sector
times  510 - ($ - $$) db 0
dw 0xAA55 ; intel machines are little-endian

buffer:

