    LOAD_ROOT:
     
     ; compute size of root directory and store in "cx"
     
          xor     cx, cx
          xor     dx, dx
          mov     ax, 0x0020                      ; 32 byte directory entry
          mul     WORD [bpbRootEntries]           ; total size of directory
          div     WORD [bpbBytesPerSector]        ; sectors used by directory
          xchg    ax, cx
          
     ; compute location of root directory and store in "ax"
     
          mov     al, BYTE [bpbNumberOfFATs]       ; number of FATs
          mul     WORD [bpbSectorsPerFAT]          ; sectors used by FATs
          add     ax, WORD [bpbReservedSectors]    ; adjust for bootsector
          mov     WORD [datasector], ax            ; base of root directory
          add     WORD [datasector], cx
          
     ; read root directory into memory (7C00:0200)
     
          mov     bx, 0x0200                        ; copy root dir above bootcode	