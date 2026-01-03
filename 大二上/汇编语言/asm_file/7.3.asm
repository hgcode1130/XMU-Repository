DATA SEGMENT
    DBL_WORDS LABEL DWORD
    REPT 100
        DW (($ - DBL_WORDS) / 4 + 1) * 2 ; 高字部分：依次生成 2, 4, 6, ..., 200
        DW 0                             ; 低字部分：固定为 0
    ENDM
DATA ENDS

CODE SEGMENT
    ASSUME CS:CODE, DS:DATA

START:
    MOV AX, DATA
    MOV DS, AX

    ; 程序结束
    MOV AH, 4CH
    INT 21H

CODE ENDS
    END START

