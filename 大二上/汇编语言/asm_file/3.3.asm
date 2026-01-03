;数据段：
DATAS SEGMENT
	NUMW dw 0F000h ; 存放 16 位无符号数，范围 565535
	SHANG dw 0
	YUSHU dw 0
DATAS ENDS
;堆栈段：
STACKS SEGMENT
	db 100 dup (?) ; 堆栈段
STACKS ENDS

;代码段实现 16 位无符号数除法运算：
CODES SEGMENT
	ASSUME	CS:CODES,DS:DATAS,SS:STACKS
START:
	mov AX,DATAS
	mov DS,AX
	mov ax,NUMW
	mov dx,0h
	mov bx,0FFF6H
	idiv bx 	;bx 中存放除数
	mov SHANG,ax
	mov YUSHU,dx
	mov AH,4CH
	INT 21H
CODES ENDS	
	END START	
