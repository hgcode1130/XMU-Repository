DATAS SEGMENT
	bvar dw 16
	wvar db 4*3
	dvar DD 4294967295
	DD -4294967295
	qvar dq ?
	dw 1,2,3,4,5
	tvar dt 2345
	abc dw 'ab','c','b','cd'
	msg db 'hello', 13, 10,'s'
	bbuf DF 'day'
	db 'day'
	dt 'xiamen','university!'
	dbuf dq 10 dup('1234')
	db 10 dup('1234')
DATAS ENDS

STACKS SEGMENT
    ;此处输入堆栈段代码
STACKS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS,SS:STACKS
START:
    MOV AX,DATAS
    MOV DS,AX
    MOV AH,4CH
    INT 21H
CODES ENDS
    END START

