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
    mov al, 0F7h
   	sar al, 1;����-5
   	mov bl, 2
   	mov al, 0f7h
   	idiv bl;����123��7b����������1
    MOV AH,4CH
    INT 21H
CODES ENDS
    END START


