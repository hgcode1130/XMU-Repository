DATAS SEGMENT
    ;此处输入数据段代码  
DATAS ENDS

STACKS SEGMENT
    ;此处输入堆栈段代码
STACKS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS,SS:STACKS
START:
    MOV AX,DATAS
    MOV DS,AX
    mov cx, 4 ; 设置循环次数为 4
	loop1:
    shr dx, 1 ; 将 ax 右移一位
    rcr ax, 1 ; 将 dx 右移一位，同时将 ax 的最高位移入 dx 的最低位
    loop loop1
    MOV AH,4CH
    INT 21H
CODES ENDS
    END START

