#include <config.h>

#define BUSY 1
#define NF_BASE   0x4E000000  //Nand Flash配置寄存器基地址

#define __REGb(x) (*(volatile unsigned char *)(x))
#define __REGi(x) (*(volatile unsigned int  *)(x))

#define NFCONF __REGi(NF_BASE + 0x0 )  //通过偏移量还是得到配置寄存器基地址
#define NFCONT __REGi(NF_BASE + 0x4 )  //通过偏移量得到控制寄存器基地址
#define NFCMD  __REGb(NF_BASE + 0x8 )  //通过偏移量得到指令寄存器基地址
#define NFADDR __REGb(NF_BASE + 0xC )  //通过偏移量得到地址寄存器基地址
#define NFDATA __REGb(NF_BASE + 0x10)  //通过偏移量得到数据寄存器基地址
#define NFSTAT __REGb(NF_BASE + 0x20)  //通过偏移量得到状态寄存器基地址

#define NAND_CHIP_ENABLE  (NFCONT &= ~(1<<1))  //Nand片选使能
#define NAND_CHIP_DISABLE (NFCONT |= (1<<1))   //取消Nand片选
#define NAND_CLEAR_RB     (NFSTAT |= BUSY)
#define NAND_DETECT_RB    { while(!(NFSTAT & BUSY));}


#define NAND_SECTOR_SIZE  2048
#define NAND_BLOCK_MASK   (NAND_SECTOR_SIZE - 1)

static void s3c2440_write_addr_lp(unsigned int addr)
{
 int i;
 volatile unsigned char *p = (volatile unsigned char *)&NFADDR;
 int col, page;

 col = addr & NAND_BLOCK_MASK;
 page = addr / NAND_SECTOR_SIZE;
       
 *p = col & 0xff;   /* Column Address A0~A7 */
   for(i=0; i<10; i++);  
 *p = (col >> 8) & 0x0f;  /* Column Address A8~A11 */
   for(i=0; i<10; i++);
 *p = page & 0xff;   /* Row Address A12~A19 */
   for(i=0; i<10; i++);
 *p = (page >> 8) & 0xff; /* Row Address A20~A27 */
   for(i=0; i<10; i++);                                                            
 *p = (page >> 16) & 0x01; /* Row Address A28~A29 */
   for(i=0; i<10; i++);                                                                                         

 }


/* low level nand read function */
int nand_read_ll(unsigned char *buf, unsigned long start_addr, int size)
{
    int i, j;

    if ((start_addr & NAND_BLOCK_MASK) || (size & NAND_BLOCK_MASK)) 
    {
        return -1; //地址或长度不对齐
    }

    NAND_CHIP_ENABLE; //选中Nand片选

    for(i = start_addr; i < (start_addr + size);) 
    {   
        //发出READ0指令
        //NAND_CLEAR_RB;
        NFCMD = 0;

        s3c2440_write_addr_lp(i);
        //2k page
  NFCMD = 0x30;

  NAND_DETECT_RB;

        for(j=0; j < NAND_SECTOR_SIZE; j++, i++) 
        {
            *buf = NFDATA;
            buf++;
        }
    }

    NAND_CHIP_DISABLE; //取消片选信号

    return 0;
}
