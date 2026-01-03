DATAS SEGMENT
    NUM EQU 5
	DATALIST DW -1, 0, 2, 5, 4,?  
DATAS ENDS

STACKS SEGMENT

STACKS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS,SS:STACKS
START:
    MOV AX,DATAS
    MOV DS,AX
    mov cx, NUM
    mov bx, 0
    mov ax, 0
    loop_sum:
        add ax, DATALIST[bx]
        add bx, 2
    loop loop_sum
    mov DATALIST[bx - 2], ax
    MOV AH,4CH
    INT 21H
CODES ENDS
    END START

