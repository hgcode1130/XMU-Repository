CHECK MACRO VAR
    CMP VAR, 5         ; �Ƚ� VAR �� 5
    JBE SKIP            ; ��� VAR <= 5��������� ADD ָ��
    REPT 10                 ; �ظ�ִ�� 10 ��
        ADD AX, AX          ; ָ�� ADD AX, AX
    ENDM
SKIP:
ENDM

DATA SEGMENT
    byteX DB 6          
DATA ENDS

CODE SEGMENT
    ASSUME CS:CODE, DS:DATA

START:
    MOV AX, DATA
    MOV DS, AX
    MOV AL, byteX
    CHECK AL
    ; �������
    MOV AH, 4CH
    INT 21H

CODE ENDS
    END START

