LOGICAL MACRO OP, REG1, REG2
    &OP &REG1, &REG2
ENDM

DATA SEGMENT
    VALUE1 DW 0F0Fh  
    VALUE2 DW 0A0A0h  
    RESULT DW ?       
DATA ENDS

CODE SEGMENT
    ASSUME CS:CODE, DS:DATA

START:
    MOV AX, DATA    
    MOV DS, AX

    MOV AX, VALUE1       ; ���ص�һ��ֵ�� AX
    MOV BX, VALUE2       ; ���صڶ���ֵ�� BX

    ; ʹ�� LOGICAL ��
    LOGICAL AND, AX, BX  ; ִ�� AX = AX AND BX
    MOV RESULT, AX       ; ������洢�� RESULT

    LOGICAL OR, AX, BX   ;  AX = AX OR BX
    LOGICAL XOR, AX, BX  ; AX = AX XOR BX
    LOGICAL TEST, AX, BX

    ; ��������
    MOV AH, 4CH
    INT 21H

CODE ENDS
    END START

