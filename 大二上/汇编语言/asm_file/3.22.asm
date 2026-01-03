
DATA SEGMENT PARA 'DATA'
    array DB 100 DUP(?)
DATA ENDS

STACK SEGMENT PARA STACK 'STACK'
    DB 100 DUP(?)
STACK ENDS

CODE SEGMENT 'code'
    ASSUME CS:CODE, DS:DATA, ES:DATA, SS:STACK
ORG 100H
start:
    mov ax, DATA
    mov ds, ax
    mov es, ax
    mov cx, 100
    mov di, 0
    mov al, 64H
    loop_set:
        mov [array + di], al
        inc di
    loop loop_set
    mov ah, 4ch
    int 21h
CODE ENDS
END start
