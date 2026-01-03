DATAS SEGMENT
    PACKED DB 52h, 10h, 52h, 10h, 52h, 10h, 52h, 10h, 52h, 10h ; 示例的20位压缩BCD数，可自行修改
    UNPACKED DB 20 DUP(?)
    MSG DB 'The unpacked BCD numbers are: $'
DATAS ENDS

STACKS SEGMENT
    DW 100 DUP(?)
STACKS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS,SS:STACKS
START:
    MOV AX,DATAS
    MOV DS,AX

    MOV DX, 10 ; 循环次数，因为要处理10个字节单元的压缩BCD数
    MOV CL, 4 ; 每次处理4位（压缩BCD数特性）
    MOV SI, 0
    MOV DI, 0

CONVERT:
    MOV AL, [SI + PACKED]
    MOV AH, AL
    AND AL, 0FH ; 取低4位作为非压缩BCD数的低位
    MOV [DI + UNPACKED], AL
    ADD DI, 1 ; 结果存储单元偏移量增加1
    SHR AH, CL ; 将高4位移动到低4位
    MOV [DI + UNPACKED], AH ; 存储高4位作为非压缩BCD数的高位
    ADD DI, 1 ; 结果存储单元偏移量再增加1
    ADD SI, 1 ; 源数据单元偏移量增加1
    DEC DX
    JNZ CONVERT

    MOV AH, 9
    MOV DX, OFFSET MSG
    INT 21H

    MOV CX, 20
    MOV SI, 0
OUTPUT:
    MOV DL, [SI + UNPACKED]
    ADD DL, 30H 
    MOV AH, 2
    INT 21H
    ADD SI, 1
    DEC CX
    JNZ OUTPUT

    MOV AH, 4CH
    INT 21H

CODES ENDS
    END START

