DATAS SEGMENT
    ; ���ݶο��������ﶨ������ȣ���������Ҫ
DATAS ENDS

STACKS SEGMENT
    ; ��ջ�ο��������ﶨ���ջ�ռ䣬��������Ҫ
STACKS ENDS

CODES SEGMENT
    ASSUME CS:CODES, DS:DATAS, SS:STACKS
START:
    MOV AX, DATAS
    MOV DS, AX

    ; �˴��������δ���
    MOV AX, 0 
    CMP AX, -1       ; �Ƚ�AX�Ƿ�С�ڵ��� -1
    JLE SET_MINUS_1  ; ���С�ڵ��� -1����ת��SET_MINUS_1
    CMP AX, 1        ; �Ƚ�AX�Ƿ�С��1
    JL SET_ZERO      ; ���С��1����ת��SET_ZERO
    ; ����������㣬����AXΪ1
    MOV AX, 1
    JMP END_PROGRAM  ; ��ת���������
SET_MINUS_1:
    MOV AX, -1       ; ����AXΪ -1
    JMP END_PROGRAM  ; ��ת���������
SET_ZERO:
    MOV AX, 0        ; ����AXΪ0
END_PROGRAM:
    MOV AH, 4CH
    INT 21H
CODES ENDS
    END START
