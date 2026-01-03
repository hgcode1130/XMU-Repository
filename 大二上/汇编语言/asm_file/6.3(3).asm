DATAS SEGMENT
    ARRAY DB 1h,2h,3h,5h,6h,8h,9h,10h,15h,20h
DATAS ENDS

STACK SEGMENT
    DW 256 DUP(0) ; 定义堆栈空间
STACK ENDS

CODES SEGMENT
    ASSUME CS:CODES, DS:DATAS, SS:STACK

START:
MAIN:
    MOV AX, DATAS
    MOV DS, AX          ; 初始化数据段

    MOV AX, STACK       ; 初始化堆栈段
    MOV SS, AX
    MOV SP, 256         ; 设置堆栈指针

    ; 设置参数（通过堆栈传递）
    MOV AX, 14H         ; 要查找的值 W
    PUSH AX             ; 压入 W 到堆栈

    LEA BX, ARRAY       ; 获取数组的地址（存入 BX）
    PUSH BX             ; 压入数组地址到堆栈

    CALL FACT           ; 调用子程序

    ; 程序结束
    MOV AH, 4CH
    INT 21H

FACT PROC
	PUSH BP
	MOV BP,SP
	PUSH DX
    PUSH SI
	 ; 从堆栈中弹出参数
    MOV SI,[BP + 4]              ; 弹出数组地址到 SI
    MOV DX,[BP + 6]              ; 弹出要查找的值 W 到 DX
    ; 保存调用者现场
    PUSH AX
    PUSH BX
    PUSH CX
    
    MOV CX, 10          ; 设置循环次数
    MOV BX, 0
    MOV AX, -1

Looop:
    INC AX
    MOV BX, AX          ; 使用 BX 存储偏移值
    MOV BL, [SI + BX]   ; 合法的寻址方式
    CMP BL, DL          ; 比较 BL 和 W（存储在 DL 中）
    JE case1            ; 如果找到，跳转到 case1
    JG case2            ; 如果大于 W，跳转到 case2
    LOOP Looop
    JMP case2           ; 如果遍历结束没有找到，跳转到 case2

case1:
    MOV AH, 02
    MOV DL, 'Y'         ; 输出 'Y'
    INT 21H
    JMP end_case

case2: 
    ; 将 W 插入数组并后移元素
    PUSH AX
    ADD AX, CX
lop:
    SUB AX, 1H
    MOV BX, AX          ; 使用 BX 存储偏移值
    PUSH DX
    MOV DX, [SI + BX]
    MOV [SI + BX + 1], DX
    POP DX
    LOOP lop
    ; 将 W 的值存入数组
    POP AX
    MOV BX, AX
    MOV AL, DL
    MOV [SI + BX], AL

end_case:
    ; 恢复调用者现场
    POP CX
    POP BX
    POP AX
	POP SI
    POP DX
    POP BP
    RET 4
FACT ENDP

CODES ENDS
    END START


