MOVESTR MACRO strN, dstr, sstr
    MOV CX, strN          ; 设置字符传送的计数
    LEA SI, sstr          ; 将源字符串地址加载到 SI
    LEA DI, dstr          ; 将目标字符串地址加载到 DI
    CLD                   ; 确保方向标志位清零
    REP MOVSB             ; 使用 REP MOVSB 指令重复传送字符
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

    MOVESTR 12, DSTR, SSTR ; 将 SSTR 中的 12 个字符传送到 DSTR

    ; 程序结束
    MOV AH, 4CH
    INT 21H

CODES ENDS
    END START

