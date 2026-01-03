
; 数据段 (DATAS SEGMENT)
DATAS SEGMENT
X DB 5        ; 定义字节变量 X 并赋值为 5
Y DB 4        ; 定义字节变量 Y 并赋值为 4
Z DB ?        ; 定义字节变量 Z，未初始化
Z1 DB ?       ; 定义字节变量 Z1，未初始化
MSG DB 'the result is : $'  ; $ 是字符串结束符 
DATAS ENDS

;堆栈段 (STACKS SEGMENT)
STACKS SEGMENT
STACKS ENDS
;这个段是空的，没有定义具体的堆栈，但在 DOS 汇编程序中，通常需要为堆栈预留空间。
;代码段 (CODES SEGMENT)
CODES SEGMENT
ASSUME CS:CODES, DS:DATAS
;这行代码告诉汇编器假设 CS (代码段寄存器) 指向 CODES 段，而 DS (数据段寄存器) 指向 DATAS 段。
;主要代码逻辑：
START:
MOV AX, DATAS       ; 将数据段的地址加载到AX寄存器
MOV DS, AX          ; 设置DS指向数据段
; 显示提示信息  
LEA DX, MSG        ; 加载提示信息的地址到 DX  
MOV AH, 09h        ; 准备调用 DOS 功能 09h 显示字符串  
INT 21h 

MOV AL, X           ; 将X的值(5)移动到AL寄存器
ADD AL, Y           ; 将Y的值(4)加到AL中，结果是9

MOV BL, 8
IMUL BL             ; 用AL中的9乘以8，结果存储在AX中，AX = 72

MOV BL, X           ; 将X的值(5)移动到BL
MOV BH, 0           ; 将BH清零，使BX = 0005
SUB AX, BX          ; AX = AX - BX (72 - 5 = 67)，AX = 67

MOV BL, 2
IDIV BL             ; 用AX中的值除以2，商存储在AL，余数存储在AH (67 / 2 = 33, 余数 1)
MOV Z, AL           ; 将商(33)存入Z
MOV Z1, AH          ; 将余数(1)存入Z1

MOV AL, Z           ; 将Z的值(33)移动到AL
MOV AH, 0           ; 清空AH，使AX仅有33
MOV BL, 10
DIV BL              ; 用10除以AX(33)，商存储在AL，余数存储在AH (33 / 10 = 3, 余数 3)

MOV DX, AX          ; 将结果存入DX，DX = 0303h
ADD DX, 3036h       ; 处理ASCII码，将DX中的值转换为字符代码

MOV AH, 2           ; 准备使用DOS中断服务 02h (显示字符)
INT 21h             ; 显示AL中的字符（十位数）


MOV DL, DH          ; 准备显示个位数
MOV AH, 2           ; 再次调用中断服务显示
INT 21H
 
MOV AH, 4CH         ; 正常终止程序
INT 21H
CODES ENDS  
END START
