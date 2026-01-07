#ifndef __FS3399_GRF_H__
#define __FS3399_GRF_H__

//通用寄存器文件——General Register Files (GRF)
#define GRF_BASE	0xFF770000

//功能复用寄存器
#define    GRF_GPIO4A_IOMUX    		 (*(volatile unsigned int *)(GRF_BASE + 0xe020))
#define    GRF_GPIO4B_IOMUX    		 (*(volatile unsigned int *)(GRF_BASE + 0xe024))
#define    GRF_GPIO4C_IOMUX          		(*(volatile unsigned int *)(GRF_BASE + 0xe028))

#endif 
