DATAS SEGMENT
    array DB 02H, 07H, 0BH, 0FH, 13H, 1CH, 24H, 39H, 40H, 57H, 68H 
    target DB 79H
    len EQU $ - array 
    FOUND_MSG DB 'Found two numbers whose sum is the target value!$'
    NOT_FOUND_MSG DB 'No two numbers in the array sum to the target value!$'
DATAS ENDS

STACKS SEGMENT
    DW 100 DUP(?)
STACKS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS,SS:STACKS
START:
    MOV AX,DATAS
    MOV DS,AX

    MOV SI, 0 ; 头指针，指向数组起始位置
    MOV DI, len - 1 ; 尾指针，指向数组末尾位置

FIND_SUM:
    MOV AL, array[SI]
    MOV AH, array[DI]
    ADD AL, AH ; 计算两数之和

    CMP AL, target ; 比较两数之和与目标值
    JE FOUND ; 如果相等，说明找到了
    JL INCREMENT_START ; 如果小于目标值，头指针向后移动
    JG DECREMENT_END 

INCREMENT_START:
    INC SI
    JMP FIND_SUM

DECREMENT_END:
    DEC DI
    JMP FIND_SUM

FOUND:
    MOV AH, 9
    MOV DX, OFFSET FOUND_MSG
    INT 21H
    JMP EXIT

NOT_FOUND:
    MOV AH, 9
    MOV DX, OFFSET NOT_FOUND_MSG
    INT 21H

EXIT:
    MOV AH, 4CH
    INT 21H

CODES ENDS
    END START
