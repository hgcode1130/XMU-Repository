DATAS SEGMENT
    ;此处输入数据段代码
    bvar db 16
    wvar dw 4*3
    dvar dd 4294967295
    qvar dq ?
    	 db 1,2,3,4,5
    tvar dt 2345
     abc db 'a', 'b', 'c'
    msg db 'hello', 13, 10,'s','$'
    bbuf db 12 dup('month')
    dbuf dd 25 dup(?)  
DATAS ENDS

STACKS SEGMENT
    ;此处输入堆栈段代码
STACKS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS,SS:STACKS
START:
    MOV AX,DATAS
    MOV DS,AX
    ;此处输入代码段代码
    MOV AX, SEG msg
	MOV DS, AX
	MOV DX, OFFSET msg
	MOV AH, 9
	INT 21H
    MOV AH,4CH
    INT 21H
CODES ENDS
    END START
