DATA SEGMENT
     A DW 4
     B DW 4
DATA ENDS
STACK SEGMENT
      DW 10 DUP(?)
TOP LABEL WORD
STACK ENDS	  
CODE SEGMENT
   ASSUME CS:CODE,SS:STACK,DS:DATA 
MAIN PROC FAR
     MOV AX,STACK
	 MOV SS,AX
	 LEA SP,TOP
	 MOV AX,DATA 
	 MOV DS,AX	 
	 MOV AX,A
	 MOV BX,B
	 TEST AX,1
	 JZ L1 
	 TEST BX,1
	 JZ L2 
	 INC AX
	 INC BX
	 MOV A,AX
	 MOV B,BX
	 JMP L2  
  L1:TEST BX,1
     JZ  L2 
	 XCHG AX,BX
	 MOV A,AX
	 MOV B,BX
  L2:MOV AH,4CH
     INT 21H
MAIN ENDP
CODE ENDS
     END MAIN 

