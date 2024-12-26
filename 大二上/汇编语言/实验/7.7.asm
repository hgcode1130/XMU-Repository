Change      macro  buffer
            lea bx,buffer
again:      mov al,[bx]
            cmp al,'$'	;若到达字符串结尾，退出
            je done
            cmp al,'A'	;判断是否大于A
            jae next1
            jmp done1
next1:      cmp al,'Z'	;判断是否小于Z
            ja  done1
            add al,20h	;满足，大写转小写
            mov byte ptr [bx],al
done1:      inc bx	;进入下一个字符
            jmp again
done:
            endm
DATAS SEGMENT
    S db 'HelLo WolRD!','$'
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
    Change S
    MOV AH,4CH
    INT 21H
CODES ENDS
    END START




