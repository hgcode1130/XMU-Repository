data segment
    ; 定义数组存放学生成绩
    scores db 95, 67, 85, 45, 74, 88, 56, 92, 67, 99
    ; 定义存放统计结果的单�?
    scoreA db 0   ; 90~100�?
    scoreB db 0   ; 80~89�?
    scoreC db 0   ; 70~79�?
    scoreD db 0   ; 60~69�?
    scoreE db 0   ; 0~59�?
data ends

code segment
    assume cs:code, ds:data
start:
    ; 初始化数据段
    mov ax, data
    mov ds, ax

    ; 初始化计数器�?
    mov byte ptr scoreA, 0
    mov byte ptr scoreB, 0
    mov byte ptr scoreC, 0
    mov byte ptr scoreD, 0
    mov byte ptr scoreE, 0

    ; 设置数组指针指向成绩数组的起始位�?
    lea si, scores

    ; 设置数组长度（在本例中为10�?
    mov cx, 10

    ; 调用统计子程�?
    call countScores

    ; 退出程�?
    mov ax, 4C00h
    int 21h

; 统计成绩分布的子程序
; 入口参数：学生成绩数组的地址，长度（cx�?
; 入口：si - 数组指针，cx - 数组长度
countScores proc near
    ; 遍历数组中的成绩
    s:
        ; 读取当前成绩
        mov al, [si]
        
        ; 判断成绩的区�?
        ; 0~59分区
        cmp al, 60
        jl scoreE_inc
        ; 60~69分区
        cmp al, 70
        jl scoreD_inc
        ; 70~79分区
        cmp al, 80
        jl scoreC_inc
        ; 80~89分区
        cmp al, 90
        jl scoreB_inc
        ; 90~100分区
        scoreA_inc:
            inc byte ptr scoreA
            jmp next

        scoreB_inc:
            inc byte ptr scoreB
            jmp next

        scoreC_inc:
            inc byte ptr scoreC
            jmp next

        scoreD_inc:
            inc byte ptr scoreD
            jmp next

        scoreE_inc:
            inc byte ptr scoreE

        next:
        ; 移动到下一个成�?
        inc si
        loop s
    ret
countScores endp

code ends
end start

