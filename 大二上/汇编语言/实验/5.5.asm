DATAS SEGMENT
	D DB 3 DUP(?); ���������ȱ��浽D����
	D1 DW ?
	D2 DW ?
	D3 DW ?
	D4 DB 30h
	MESSAGE DB 'please input three number(hex��1Byte):',13,10,'$' 
    ;�˴��������ݶδ���  
DATAS ENDS

STACKS SEGMENT
    ;�˴������ջ�δ���
STACKS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS,SS:STACKS
START:
    MOV AX,DATAS
    MOV DS,AX
    LEA DX,MESSAGE
    MOV AH,09H ;dos 9�Ź��ܵ�������ַ�������$��β
    INT 21H   ; �����ʾ
    MOV CX, 3H        ;��������3����
    MOV SI,OFFSET D;���üĴ������Ѱַ
INPUT: MOV BX ,0; �������������ʱ����BX,��ʼ��λ0
	MOV AH,01H  ; dos 1�Ź��ܵ�������1���ַ���AL
	INT 21H  	; �����ֽڸ�λ
	CMP Al, 'a' ; �������a..f
	JB C1
	SUB AL,20H; ���Сд��ĸ
C1: CMP AL,'A' ;   
    JB C2
    SUB AL,7H; �����֡�9����7
C2: SUB AL,30H
	MOV BL,AL
	SHL BL,1
	SHL BL,1
	SHL BL,1
	SHL BL,1; ѭ������4λ���Ƶ���λ
	INT 21H
	CMP Al, 'a' ; �������a..f
	JB C3
	SUB AL,20H; ���Сд��ĸ
C3: CMP AL, 'A' ;  
    JB C4
    SUB AL,7H; �����֡�9����7
C4: SUB AL,30H
	ADD BL,AL
	MOV [SI], BL;�����������ڴ�D��λ��
	INC SI ; si+1
	MOV AH,02H ; dos 2�Ź������1���ַ�
	MOV DL,13 ;����ַ�
	INT 21H  ; ���\rʹ�ñ�ʾ�������������,dosϵͳ����Ҫ������
	MOV DL,10
	INT 21H ; ����\n ����
	LOOP INPUT ;ѭ��
	MOV SI,OFFSET D
	MOV AX,0H; ��ΪAX16,D8λ����Al,����ax��ʼ��Ϊ0
    MOV AL,BYTE PTR [SI]
    MOV D1,AX
    MOV AL,BYTE PTR [SI+1]
    MOV D2,AX
    MOV AL,BYTE PTR [SI+2]
    MOV D3,AX ; �����ݷֱ�����D1,D2,D3
    MOV AX,D1
    CMP AX,D2
    JE L1 ; D1��D2�����תL1λ��
    CMP AX,D3
    JE L2
    MOV AX,D2
    CMP AX,D3
    JE L2
    JMP L
L1: MOV D4,31H
	CMP AX,D3
	JNE L
	MOV D4,32H
	JMP L
L2: MOV D4,31H
	JMP L
L:	MOV AH,02H ; dos 2�Ź������1���ַ�
	MOV DL,D4
	INT 21H
	MOV AH,4CH  ; �������һ���ַ���������ͣ���򣬹ۿ����
	INT 21H
CODES ENDS
    END START


