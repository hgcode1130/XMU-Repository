#MIPS����    test4-1.asm    ð�ݷ����򣨽������У��Ӵ�С��                       

#��������ʼ��ַ��0                                                                			RAM��Ӧ000

#IRQ0�жϷ���������ڵ�ַ��1024  =  400H     				RAM��Ӧ100                 
#IRQ1�жϷ���������ڵ�ַ��1536  =  600H     				RAM��Ӧ180
#IRQ2�жϷ���������ڵ�ַ��2048  =  800H    				RAM��Ӧ200
#IRQ3�жϷ���������ڵ�ַ��2560  =  A00H    				RAM��Ӧ280

#5������5��1��3��2��4����ŵ���ʼ��ַ��3072          			RAM��Ӧ300

#IRQ0�жϷ�����򽫵�ַΪ3328�Ĵ洢��Ԫ�����ݼ�1         			RAM��Ӧ340
#IRQ0�жϷ�����򽫵�ַΪ3392�Ĵ洢��Ԫ�����ݼ�1         			RAM��Ӧ350
#IRQ0�жϷ�����򽫵�ַΪ3456�Ĵ洢��Ԫ�����ݼ�1         			RAM��Ӧ360
#IRQ0�жϷ�����򽫵�ַΪ3520�Ĵ洢��Ԫ�����ݼ�1         			RAM��Ӧ370

#��ջ����ʼ��ַ��  3840                           				RAM��Ӧ3c0




.text  

main:
	addi $sp,$zero,3840  	  #�����жϷ�������ջ�ĵ�ַ

 	addi $s0,$zero,5                        #��1����=5�������޸ģ����浽(3072+0)
 	sw $s0,3072($zero)

 	addi $s0,$zero,1                        #��2����=1�������޸ģ����浽(3072+4)
 	sw $s0,3076($zero)

 	addi $s0,$zero,3                        #��3����=3�������޸ģ����浽(3072+8)
 	sw $s0,3080($zero)

 	addi $s0,$zero,2                        #��4����=2�������޸ģ����浽(3072+12)
	sw $s0,3084($zero)

 	addi $s0,$zero,4                        #��5����=4�������޸ģ����浽(3072+16)
	sw $s0,3088($zero)

 	addi $s0,$zero,3072                  #$s0=3072                              �������俪ʼ��ַ
 	addi $s1,$zero,3088  	  #$s1=3088=3072+5*4-4       �������������ַ         

sort_loop:
 	lw $s3,0($s0)                     	  #$s3=($s0)
	lw $s4,0($s1)                	  #$s4=($s1)
 	slt $t0,$s3,$s4                	  #���$s3<$s4������$t0=1��������$t0=0        ��������         �Ӵ�С
 	beq $t0,$zero,sort_next   	  #���$t0=0����תsort_nent       
 	sw $s3,0($s1)                	  #����($s0)��($s1)
	sw $s4,0($s0)                   	  #����($s0)��($s1)

sort_next:
	addi $s1,$s1,-4                          #$s1-4 -> $s1
 	beq $s0,$s1,loop1                     #���$s0=$s1����תloop1   
 	beq $zero,$zero,sort_loop        #תsort_loop

loop1:
  	addi $s0,$s0,4                           #$s0+4 -> $s0
	addi $s1,$zero,3088                 #$s1=3088=3072+5*4-4   �������������ַ                     
 	beq $s0,$s1,loop2                    #���$s0=$s1����תloop2
 	beq $zero,$zero,sort_loop       #תsort_loop

loop2:
 	beq $zero,$zero,loop2	  #תloop2             ��ѭ��







IRQ0:                                                       #IRQ0�жϷ���������ڵ�ַ��1024   =   400H    		RAM��Ӧ100            

	sw $s0, 0($sp)		#push registers  ��Ҫ�����жϳ����õ��ļĴ���                 $s0    $s1 
	addi $sp, $sp, 4
	sw $s1, 0($sp)
	addi $sp, $sp, 4
  
  	addi $s1,$zero,3328              #RAM��Ӧ340
  	lw $s0,0($s1)
  	addi $s0,$s0,1
  	sw $s0,0($s1)		#ȡ��(3328)��Ԫ�����ݣ���1���ٱ��浽�����Ԫ��

	addi $sp, $sp, -4		#pop registers
	lw $s1, 0($sp)
	addi $sp, $sp, -4
	lw $s0, 0($sp)

  	eret









IRQ1: 				#IRQ0�жϷ���������ڵ�ַ��1536     =   600H  		RAM��Ӧ180            

	sw $s0, 0($sp)		#push registers  ��Ҫ�����жϳ����õ��ļĴ���                 $s0    $s1 
	addi $sp, $sp, 4
	sw $s1, 0($sp)
	addi $sp, $sp, 4

  	addi $s1,$zero,3392              #RAM��Ӧ350
  	lw $s0,0($s1)
  	addi $s0,$s0,1
  	sw $s0,0($s1)		#ȡ��(3392)��Ԫ�����ݣ���1���ٱ��浽�����Ԫ��

 	addi $sp, $sp, -4		#pop registers
	lw $s1, 0($sp)
	addi $sp, $sp, -4
	lw $s0, 0($sp)

  	eret








IRQ2: 				#IRQ0�жϷ���������ڵ�ַ��2048       =  800H			RAM��Ӧ200            

	sw $s0, 0($sp)		#push registers  ��Ҫ�����жϳ����õ��ļĴ���                 $s0    $s1 
	addi $sp, $sp, 4
	sw $s1, 0($sp)
	addi $sp, $sp, 4

  	addi $s1,$zero,3456             #RAM��Ӧ360
  	lw $s0,0($s1)
  	addi $s0,$s0,1
  	sw $s0,0($s1)		#ȡ��(3456)��Ԫ�����ݣ���1���ٱ��浽�����Ԫ��

	addi $sp, $sp, -4		#pop registers
	lw $s1, 0($sp)
	addi $sp, $sp, -4
	lw $s0, 0($sp)

  	eret







IRQ3: 				#IRQ0�жϷ���������ڵ�ַ��2560       =  A00H		RAM��Ӧ280        
    
	sw $s0, 0($sp)		#push registers  ��Ҫ�����жϳ����õ��ļĴ���                 $s0    $s1 
	addi $sp, $sp, 4
	sw $s1, 0($sp)
	addi $sp, $sp, 4

  	addi $s1,$zero,3520               #RAM��Ӧ370
  	lw $s0,0($s1)
  	addi $s0,$s0,1
  	sw $s0,0($s1)		#ȡ��(3520)��Ԫ�����ݣ���1���ٱ��浽�����Ԫ��

	addi $sp, $sp, -4		#pop registers
	lw $s1, 0($sp)
	addi $sp, $sp, -4
	lw $s0, 0($sp)

  	eret



