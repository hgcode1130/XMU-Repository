DATAS SEGMENT
    ;�˴��������ݶδ���  
DATAS ENDS

STACKS SEGMENT
    ;�˴������ջ�δ���
STACKS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS,SS:STACKS
START:
    MOV AX,DATAS
    MOV DS,AX
    xor ah,ah;��ah���
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
