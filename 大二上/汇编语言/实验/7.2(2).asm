DATA SEGMENT

DATA ENDS

CODE SEGMENT
    ASSUME CS:CODE, DS:DATA

START:
    MOV AX, DATA      ; ��ʼ�����ݶμĴ���
    MOV DS, AX
    ; .repeat ʾ��
    mov ax, 0
    .repeat
        MOV [BX], AX
        INC BX
        INC BX
        INC AX
    .until ax == 10

    MOV AH, 4CH       ; ������������
    INT 21H
CODE ENDS
    END START


