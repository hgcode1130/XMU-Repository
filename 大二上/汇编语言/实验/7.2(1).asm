DATA SEGMENT

DATA ENDS

CODE SEGMENT
    ASSUME CS:CODE, DS:DATA

START:
    MOV AX, DATA      ; ��ʼ�����ݶμĴ���
    MOV DS, AX
    mov ax, 0
    .while ax != 10
        MOV [BX], AX
        INC BX
        INC BX
        INC AX
    .endw
    MOV AH, 4CH       ; ������������
    INT 21H
CODE ENDS
    END START


