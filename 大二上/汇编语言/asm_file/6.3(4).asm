DATAS SEGMENT
    ARRAY DB 1h,2h,3h,5h,6h,8h,9h,10h,15h,20h ; 定义一个长度为10的数组
DATAS ENDS

STACK SEGMENT
    DW 256 DUP(0) ; 定义堆栈空间，大小为256个字
STACK ENDS

CODES SEGMENT
    ASSUME CS:CODES, DS:DATAS, SS:STACK

START:
MAIN:
    ; 初始化数据段
    MOV AX, DATAS       ; 加载数据段基址
    MOV DS, AX          ; 将数据段基址加载到DS

    ; 初始化堆栈段
    MOV AX, STACK       ; 加载堆栈段基址
    MOV SS, AX          ; 设置堆栈段寄存器
    MOV SP, 256         ; 设置堆栈顶指针

    ; 设置参数并通过堆栈传递给子程序
    MOV AX, 2H         ; 将要查找的值 W 设置为 14H
    PUSH AX             ; 压入 W 到堆栈
    LEA BX, ARRAY       ; 加载数组的起始地址到 BX
    PUSH BX             ; 压入数组地址到堆栈

    CALL FACT           ; 调用子程序 FACT

    ; 程序结束
    MOV AH, 4CH         ; DOS 中断：程序终止
    INT 21H

FACT PROC
    ; 保存调用者的栈帧信息
    PUSH BP             ; 保存 BP 寄存器
    MOV BP, SP          ; 将 SP 保存到 BP（建立栈帧）

    ; 保存调用者现场
    PUSH DX             ; 保存 DX 寄存器
    PUSH BX             ; 保存 BX 寄存器

    ; 从栈帧中提取参数
    MOV BX, [BP + 4]    ; 从栈帧获取数组地址，存到 BX
    MOV DX, [BP + 6]    ; 从栈帧获取要查找的值 W，存到 DX

    ; 保存剩余的调用者现场
    PUSH AX             ; 保存 AX
    PUSH SI             ; 保存 SI
    PUSH CX             ; 保存 CX

    ; 初始化循环
    MOV CX, 10          ; 数组长度为10，设置循环计数器
    MOV SI, -1          ; 初始化 SI（变址寄存器）

Looop:
    INC SI              ; SI 指向下一个数组元素
    MOV AL, [BX + SI]   ; 读取数组中当前元素到 AL
    CMP AL, DL          ; 比较当前数组元素 AL 和 W
    JE case1            ; 如果 AL == W，跳转到 case1
    JG case2            ; 如果 AL > W，跳转到 case2
    LOOP Looop          ; 否则继续下一次循环
    JMP case2           ; 如果遍历结束，跳转到 case2

case1:
    ; 如果找到 W，输出 'Y'
    MOV AH, 02          ; 设置 DOS 输出服务号
    MOV DL, 'Y'         ; 设置输出字符 'Y'
    INT 21H             ; 调用中断
    JMP end_case        ; 跳转到结束处理

case2:
    ; 如果未找到 W，将其插入到合适的位置
    PUSH SI             ; 将当前 SI 压栈保存
    ADD SI, CX          ; 将 SI 移动到数组末尾位置
lop:
    SUB SI, 1H          ; 从数组末尾向前遍历
    MOV AX, [SI + BX]   ; 获取当前元素
    MOV [SI + BX + 1], AX ; 将当前元素后移一位
    LOOP lop            ; 循环直到插入点
    ; 将 W 插入到数组中
    POP SI              ; 恢复插入点的 SI
    MOV [SI + BX], DL   ; 将 W 写入插入点

end_case:
    ; 恢复调用者现场
    POP CX              ; 恢复 CX
    POP SI              ; 恢复 SI
    POP AX              ; 恢复 AX
    POP BX              ; 恢复 BX
    POP DX              ; 恢复 DX
    POP BP              ; 恢复 BP
    RET 4               ; 返回，并清理栈上两个参数（数组地址和 W）

FACT ENDP

CODES ENDS
    END START


