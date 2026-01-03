DATA SEGMENT

DATA ENDS

CODE SEGMENT
    ASSUME CS:CODE, DS:DATA

START:
    MOV AX, DATA      ; 初始化数据段寄存器
    MOV DS, AX
    ; .repeat 示例
    mov ax, 0
    .repeat
        MOV [BX], AX
        INC BX
        INC BX
        INC AX
    .until ax == 10

    MOV AH, 4CH       ; 正常结束程序
    INT 21H
CODE ENDS
    END START


