stack     segment stack 
          db 100h dup(?) 
stack     ends 
data      segment 
ledtable  db 0c0h,0f9h,0a4h,0b0h,99h,92h,82h,0f8h 
          db 80h,90h,88h,83h,0c6h,0c1h,86h,8eh 
lednum    db 3 
data      ends 
code      segment 'code' 
assume    cs:code,ss:stack,ds:data 
start:    mov ax,data 
          mov ds,ax 
          lea bx,ledtable 
          mov al,lednum 
          xlat 
          mov ax,4c00h 
          int 21h 
code      ends 
          end start

