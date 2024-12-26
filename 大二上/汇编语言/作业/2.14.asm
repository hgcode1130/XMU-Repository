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
    mov al, 0F7h
   	sar al, 1;商是-5
   	mov bl, 2
   	mov al, 0f7h
   	idiv bl;商是123（7b），余数是1
    MOV AH,4CH
    INT 21H
CODES ENDS
    END START


