DATA SEGMENT
    data DB 12H, 45H, 0F3H, 6AH, 20H, 0FEH, 90H, 0C8H, 57H, 34H
    sum DB?
DATA ENDS

CODE SEGMENT
    ASSUME CS:CODE, DS:DATA
start:
    mov ax, DATA
    mov ds, ax
    mov al, 0
    mov cx, 10
    lea si, data
    loop_sum:
        add al, [si]
        inc si
    loop loop_sum
    mov sum, al
    mov ah, 4ch
    int 21h
CODE ENDS
END start
