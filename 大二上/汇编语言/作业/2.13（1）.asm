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
    xor ah,ah;将ah清空
    mov al,10
    mov bx,ax
    mov cl,3
    shl ax,cl
    add ax,bx
    add ax,bx
    MOV AH,4CH
    INT 21H
CODES ENDS
    END START
