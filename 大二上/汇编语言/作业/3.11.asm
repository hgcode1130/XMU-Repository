DATAS SEGMENT 
	my1b DB 'Personal Computer'
	my2b DB 20
	my3b DB 14H ;十六进制的 20 为 14H
	my4b DB 00010100B ;二进制的 20
	my5w DW 20 DUP(?)
	my6c EQU 100
	my7c DB 'Personal Computer'
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
    MOV AH,4CH
    INT 21H
CODES ENDS
    END START
