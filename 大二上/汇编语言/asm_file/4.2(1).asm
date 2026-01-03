DATAS SEGMENT
    COUNT DW 0 ; 用于记录BX中1的个数
DATAS ENDS

STACKS SEGMENT
    DW 100 DUP(?) ; 定义堆栈段空间
STACKS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS,SS:STACKS
START:
    MOV AX,DATAS
    MOV DS,AX

    MOV BX, 0FFFFH ; 这里可替换为任意16位二进制数
    MOV CX, 16 ; 因为BX是16位，所以循环次数为16

    MOV COUNT, 0 ; 初始化计数器为0

COUNT_LOOP:
    TEST BX, 0001H ; 测试最低位是否为1
    JZ ZERO ; 如果为0，跳转到ZERO
    INC COUNT ; 如果为1，计数器加1

ZERO:
    ROR BX, 1 ; 循环右移BX，准备测试下一位
    DEC CX
    JNZ COUNT_LOOP

    MOV AH, 4CH
    INT 21H

CODES ENDS
    END START
