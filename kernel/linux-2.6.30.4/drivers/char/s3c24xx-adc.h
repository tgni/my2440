/*
 * =====================================================================================
 *
 *       Filename:  s3c4xx-adc.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/20/2013 06:43:20 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  tonggui.ni (Nick), tonggui.ni@feixun.com.cn
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef _S3C2410_ADC_H_
#define _S3C2410_ADC_H_

#define ADC_WRITE(ch, prescale)    ((ch)<<16|(prescale))

#define ADC_WRITE_GETCH(data)    (((data)>>16)&0x7)
#define ADC_WRITE_GETPRE(data)    ((data)&0xff)

#endif /* _S3C2410_ADC_H_ */
