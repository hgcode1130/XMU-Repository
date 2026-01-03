CHECK MACRO VAR
    CMP VAR, 5         ; 比较 VAR 和 5
    JBE SKIP            ; 如果 VAR <= 5，跳过汇编 ADD 指令
    REPT 10                 ; 重复执行 10 次
        ADD AX, AX          ; 指令 ADD AX, AX
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
    ; 程序结束
    MOV AH, 4CH
    INT 21H

CODE ENDS
    END START

