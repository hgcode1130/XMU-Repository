DATA SEGMENT
    DBL_WORDS LABEL DWORD
    REPT 100
        DW (($ - DBL_WORDS) / 4 + 1) * 2 ; ���ֲ��֣��������� 2, 4, 6, ..., 200
        DW 0                             ; ���ֲ��֣��̶�Ϊ 0
    ENDM
DATA ENDS

CODE SEGMENT
    ASSUME CS:CODE, DS:DATA

START:
    MOV AX, DATA
    MOV DS, AX

    ; �������
    MOV AH, 4CH
    INT 21H

CODE ENDS
    END START

