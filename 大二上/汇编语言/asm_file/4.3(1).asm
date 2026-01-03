DATAS SEGMENT
    string DB 'This is a sample string', 0 ; 示例字符串，可替换为任意长度大于6的字符串
    len EQU $ - string ; 计算字符串长度
DATAS ENDS

STACKS SEGMENT
    DW 100 DUP(?)
STACKS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS,SS:STACKS
START:
    MOV AX,DATAS
    MOV DS,AX

    MOV DL, string ; 传送第1个字符到DL
    MOV DH, string + 5 ; 传送第6个字符到DH

    MOV AH, 4CH
    INT 21H

CODES ENDS
    END START
