MOVESTR MACRO strN, dstr, sstr
    MOV CX, strN          ; �����ַ����͵ļ���
    LEA SI, sstr          ; ��Դ�ַ�����ַ���ص� SI
    LEA DI, dstr          ; ��Ŀ���ַ�����ַ���ص� DI
    CLD                   ; ȷ�������־λ����
    REP MOVSB             ; ʹ�� REP MOVSB ָ���ظ������ַ�
ENDM

DATAS SEGMENT
    SSTR DB 'HELLO WORLD!' 
    DSTR DB 20 DUP(?)   
DATAS ENDS

STACKS SEGMENT
    DB 128 DUP(0)
STACKS ENDS

CODES SEGMENT
    ASSUME CS:CODES, DS:DATAS, SS:STACKS

START:

    MOV AX, DATAS
    MOV DS, AX
    MOV AX, DATAS
    MOV ES, AX 

    MOVESTR 12, DSTR, SSTR ; �� SSTR �е� 12 ���ַ����͵� DSTR

    ; �������
    MOV AH, 4CH
    INT 21H

CODES ENDS
    END START

