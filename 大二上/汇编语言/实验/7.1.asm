DATAS SEGMENT
    X DW 5       
    AX_VAR DW 10 
    BX_VAR DW 20 
DATAS ENDS

STACKS SEGMENT
    DB 128 DUP(0)
STACKS ENDS

CODES SEGMENT
    ASSUME CS:CODES, DS:DATAS, SS:STACKS

START:
    ; 初始化段寄存器
    MOV AX, DATAS
    MOV DS, AX
    MOV AX, STACKS
    MOV SS, AX
    MOV SP, 128

    ; 实现条件逻辑 .if(x == 5) && (ax != bx)
    MOV AX, X           ; 将 X 的值加载到 AX
    CMP AX, 5           ; 比较 X 是否等于 5
    JNE ed       ; 如果不等于 5，跳转到 ed

    MOV AX, AX_VAR  
    MOV BX, BX_VAR   
    CMP AX, BX          ; 比较 AX 和 BX 是否相等
    JE ed        ; 如果相等，跳转到 ed

    INC AX          ; AX 加 1

ed:
    ; 程序结束
    MOV AH, 4CH         ; DOS 功能号 4CH：程序结束
    INT 21H             ; 调用中断 21H

CODES ENDS
    END START

