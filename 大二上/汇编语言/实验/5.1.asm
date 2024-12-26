DATAS SEGMENT
    ; 数据段可以在这里定义变量等，本程序不需要
DATAS ENDS

STACKS SEGMENT
    ; 堆栈段可以在这里定义堆栈空间，本程序不需要
STACKS ENDS

CODES SEGMENT
    ASSUME CS:CODES, DS:DATAS, SS:STACKS
START:
    MOV AX, DATAS
    MOV DS, AX

    ; 此处输入代码段代码
    MOV AX, 0 
    CMP AX, -1       ; 比较AX是否小于等于 -1
    JLE SET_MINUS_1  ; 如果小于等于 -1，跳转到SET_MINUS_1
    CMP AX, 1        ; 比较AX是否小于1
    JL SET_ZERO      ; 如果小于1，跳转到SET_ZERO
    ; 如果都不满足，设置AX为1
    MOV AX, 1
    JMP END_PROGRAM  ; 跳转到程序结束
SET_MINUS_1:
    MOV AX, -1       ; 设置AX为 -1
    JMP END_PROGRAM  ; 跳转到程序结束
SET_ZERO:
    MOV AX, 0        ; 设置AX为0
END_PROGRAM:
    MOV AH, 4CH
    INT 21H
CODES ENDS
    END START
