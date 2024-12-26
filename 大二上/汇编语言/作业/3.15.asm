DATA SEGMENT 
	 org 100h
varw dw 1234h, 5678h
varb db 3,4
	align 4
vard dd 12345678h
	even
buff db 10 dup(?)
mess db 'Hello'
DATA ENDS

CODE SEGMENT
ASSUME CS:CODE, DS:DATA
start:
    mov ax, DATA
    mov ds, ax
  
    begin:
    mov ax, offset mess
      
    mov ax, type buff + type mess + type vard
 
    mov ax, sizeof varw + sizeof buff + sizeof mess
        
    mov ax, lengthof varw + lengthof vard
       
    mov ax, lengthof buff + sizeof varw
     
    mov ax, type begin
       
    mov ax, offset begin
      
    mov ah, 4ch
    int 21h
CODE ENDS
END start
