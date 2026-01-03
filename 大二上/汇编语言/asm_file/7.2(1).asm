DATA SEGMENT

DATA ENDS

CODE SEGMENT
    ASSUME CS:CODE, DS:DATA

START:
    MOV AX, DATA      ; 初始化数据段寄存器
    MOV DS, AX
    mov ax, 0
    .while ax != 10
        MOV [BX], AX
        INC BX
        INC BX
        INC AX
    .endw
    MOV AH, 4CH       ; 正常结束程序
    INT 21H
CODE ENDS
    END START


