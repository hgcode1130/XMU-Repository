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
    mov cx, 4 ; ����ѭ������Ϊ 4
	loop1:
    shr dx, 1 ; �� ax ����һλ
    rcr ax, 1 ; �� dx ����һλ��ͬʱ�� ax �����λ���� dx �����λ
    loop loop1
    MOV AH,4CH
    INT 21H
CODES ENDS
    END START

