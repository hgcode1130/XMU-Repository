DATAS SEGMENT 
	my1b DB 'Personal Computer'
	my2b DB 20
	my3b DB 14H ;ʮ�����Ƶ� 20 Ϊ 14H
	my4b DB 00010100B ;�����Ƶ� 20
	my5w DW 20 DUP(?)
	my6c EQU 100
	my7c DB 'Personal Computer'
DATAS ENDS

STACKS SEGMENT
    ;�˴������ջ�δ���
STACKS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS,SS:STACKS
START:
    MOV AX,DATAS
    MOV DS,AX
    ;�˴��������δ���
    MOV AH,4CH
    INT 21H
CODES ENDS
    END START
