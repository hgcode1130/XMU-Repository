DATAS SEGMENT
    X DW 5       
    AX_VAR DW 10 
    BX_VAR DW 20 
DATAS ENDS

STACKS SEGMENT
    DB 128 DUP(0)
STACKS ENDS

CODES SEGMENT
    ASSUME CS:CODES, DS:DATAS, SS:STACKS

START:
    ; ��ʼ���μĴ���
    MOV AX, DATAS
    MOV DS, AX
    MOV AX, STACKS
    MOV SS, AX
    MOV SP, 128

    ; ʵ�������߼� .if(x == 5) && (ax != bx)
    MOV AX, X           ; �� X ��ֵ���ص� AX
    CMP AX, 5           ; �Ƚ� X �Ƿ���� 5
    JNE ed       ; ��������� 5����ת�� ed

    MOV AX, AX_VAR  
    MOV BX, BX_VAR   
    CMP AX, BX          ; �Ƚ� AX �� BX �Ƿ����
    JE ed        ; �����ȣ���ת�� ed

    INC AX          ; AX �� 1

ed:
    ; �������
    MOV AH, 4CH         ; DOS ���ܺ� 4CH���������
    INT 21H             ; �����ж� 21H

CODES ENDS
    END START

