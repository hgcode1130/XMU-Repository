;�����еİ汾
.model small
.stack
.data
hex db 4bh
 
.code
.startup
    ;��ʾ��λ
    mov al,hex
    mov cl,4
    shr al,cl
    mov dl,al 
    call disp
    ;��ʾ��λ
    mov dl,hex
    and dl,0fh ;����λ��0
    call disp
    .exit 0
 
;��ʾ�ַ����ӳ���
disp PROC
    cmp dl,9
    jbe next ;���С�ڵ���9����ֱ�Ӽ�30h���������ĸ������Ҫ�����7
zimu:
    add dl,7h
next:
    add dl,30h
    ;��ʾ
    mov ah,02h
    int 21h
    ret
disp ENDP   
 
end
