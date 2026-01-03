data segment
	org 3000h
	result dw 0000h
	org 3100h
	n	db 3
data ends

code segment
	assume cs:code 
MAIN:
	mov ax,data
	mov ds,ax
	
	mov si,3100h
	mov ax,[si]
	call fact
	mov si,offset result
	mov [si],dx
	
	mov ax,4c00h
	int 21h
;阶乘子程序
;入口参数： al中存放n
;出口参数：	bx中存放n!
fact proc near
	cmp ax,0
	jne IIA
	mov bx,1
	ret
IIA:
	push ax
	dec ax
	call fact
X2:
	pop cx
	call mult
X3:
	mov bx,ax
	ret
fact endp
;无符号字节数乘法子程序
;入口参数:cx,bx中的各为一个乘数
;出口参数：ax中的为乘积
mult proc near
	mov ax,bx
	mul cx
	ret
mult endp
code ends
end MAIN

