;用xlat
 
.model small
.stack
.data
hex db 4bh
ascii db 30h,31h,32h,33h,34h,35h,36h,37h,38h,39h
      db 41h,42h,43h,44h,45h,46h
 
.code
.startup
    mov bx,offset ascii ;取得表的偏移地址，为换码做准备
    ;显示高位
    mov al,hex
    mov cl,4
    sar al,cl
    xlat      ;al<--ds:[bx+al]
    mov dl,al
    mov ah,02h
    int 21h
    ;显示低位
    mov al,hex
    and al,0fh ;高位为0
    xlat 
    mov dl,al
    mov ah,02h
    int 21h
 
    .exit 0
end
