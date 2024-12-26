;不换行的版本
.model small
.stack
.data
hex db 4bh
 
.code
.startup
    ;显示高位
    mov al,hex
    mov cl,4
    shr al,cl
    mov dl,al 
    call disp
    ;显示低位
    mov dl,hex
    and dl,0fh ;将高位置0
    call disp
    .exit 0
 
;显示字符的子程序
disp PROC
    cmp dl,9
    jbe next ;如果小于等于9，就直接加30h，如果是字母，就需要另外加7
zimu:
    add dl,7h
next:
    add dl,30h
    ;显示
    mov ah,02h
    int 21h
    ret
disp ENDP   
 
end
