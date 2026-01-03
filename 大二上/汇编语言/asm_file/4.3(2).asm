DATAS SEGMENT
    buffer DB 05H, 08H, 02H, 07H
DATAS ENDS

STACKS SEGMENT
    DW 100 DUP(?)
STACKS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS,SS:STACKS
START:
    MOV AX,DATAS
    MOV DS,AX

    MOV AL, buffer ; 取低地址的非压缩BCD码（低位）
    MOV AH, buffer + 3 ; 取高地址的非压缩BCD码（高位）

    MOV DX, 0
    SHL AH, 4 ; 将高地址的BCD码移到高4位
    OR DX, AX ; 合并到DX

    MOV AH, 4CH
    INT 21H

CODES ENDS
    END START
