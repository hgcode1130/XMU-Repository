Change      macro  buffer
            lea bx,buffer
again:      mov al,[bx]
            cmp al,'$'	;�������ַ�����β���˳�
            je done
            cmp al,'A'	;�ж��Ƿ����A
            jae next1
            jmp done1
next1:      cmp al,'Z'	;�ж��Ƿ�С��Z
            ja  done1
            add al,20h	;���㣬��дתСд
            mov byte ptr [bx],al
done1:      inc bx	;������һ���ַ�
            jmp again
done:
            endm
DATAS SEGMENT
    S db 'HelLo WolRD!','$'
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
    Change S
    MOV AH,4CH
    INT 21H
CODES ENDS
    END START




