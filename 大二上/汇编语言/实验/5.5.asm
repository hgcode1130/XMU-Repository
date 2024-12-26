DATAS SEGMENT
	D DB 3 DUP(?); 将数据首先保存到D数组
	D1 DW ?
	D2 DW ?
	D3 DW ?
	D4 DB 30h
	MESSAGE DB 'please input three number(hex，1Byte):',13,10,'$' 
    ;此处输入数据段代码  
DATAS ENDS

STACKS SEGMENT
    ;此处输入堆栈段代码
STACKS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS,SS:STACKS
START:
    MOV AX,DATAS
    MOV DS,AX
    LEA DX,MESSAGE
    MOV AH,09H ;dos 9号功能调用输出字符串，以$结尾
    INT 21H   ; 输出提示
    MOV CX, 3H        ;控制输入3个数
    MOV SI,OFFSET D;利用寄存器间接寻址
INPUT: MOV BX ,0; 将输入的数据暂时保留BX,初始化位0
	MOV AH,01H  ; dos 1号功能调用输入1个字符到AL
	INT 21H  	; 读入字节高位
	CMP Al, 'a' ; 输入的是a..f
	JB C1
	SUB AL,20H; 变成小写字母
C1: CMP AL,'A' ;   
    JB C2
    SUB AL,7H; 与数字‘9’隔7
C2: SUB AL,30H
	MOV BL,AL
	SHL BL,1
	SHL BL,1
	SHL BL,1
	SHL BL,1; 循环左移4位，移到高位
	INT 21H
	CMP Al, 'a' ; 输入的是a..f
	JB C3
	SUB AL,20H; 变成小写字母
C3: CMP AL, 'A' ;  
    JB C4
    SUB AL,7H; 与数字‘9’隔7
C4: SUB AL,30H
	ADD BL,AL
	MOV [SI], BL;将数据送往内存D的位置
	INC SI ; si+1
	MOV AH,02H ; dos 2号功能输出1个字符
	MOV DL,13 ;输出字符
	INT 21H  ; 输出\r使得表示将光标移至行首,dos系统下需要这样做
	MOV DL,10
	INT 21H ; 输入\n 换行
	LOOP INPUT ;循环
	MOV SI,OFFSET D
	MOV AX,0H; 因为AX16,D8位，用Al,所以ax初始化为0
    MOV AL,BYTE PTR [SI]
    MOV D1,AX
    MOV AL,BYTE PTR [SI+1]
    MOV D2,AX
    MOV AL,BYTE PTR [SI+2]
    MOV D3,AX ; 将数据分别送往D1,D2,D3
    MOV AX,D1
    CMP AX,D2
    JE L1 ; D1，D2相等跳转L1位置
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
L:	MOV AH,02H ; dos 2号功能输出1个字符
	MOV DL,D4
	INT 21H
	MOV AH,4CH  ; 随机输入一个字符，用来暂停程序，观看结果
	INT 21H
CODES ENDS
    END START


