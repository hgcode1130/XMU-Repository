#ifndef HAL_C_MSG_H
#define HAL_C_MSG_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>


#define LEN       24
#define Num         128
#define DEBUG     0
//GPRS
#define TXT_MODE  "AT+CMGF=1\r"
#define CHI_MODE  "AT+CMGF=0\r"
#define SET_TE    "AT+CSCS=\"GSM\"\r"
#define HAND_UP   "AT+CHUP\r"
#define NOWAITHAND_UP "ATH\r"
#define GET_PHONENUM "AT+CGSN\r"
#define GET_SIM "AT+CPIN?\r"

//GPS
#define GPS_START "AT+QGPS=1\r"
#define GPS_END   "AT+QGPSEND\r"

//获取打电话的状态
#define GET_CALL "AT+CLIP=1\r"
#define GET_CALLDSCI "AT^DSCI=1\r"
#define GET_CALLQURCCFG "AT+QURCCFG=\"URCPORT\",\"UART1\"\r"
#define SET_CALL "AT+COLP=1\r"

#define ANSWER "ATA\r"



extern int tty_usb_open();
extern int gprs_option_handle(char *phone_num);
extern int string_compare(char ch1[Num]);
extern int handup();
extern int answer_thephone();
extern char *get_callphone();
//extern void get_call_records(const char* imei);
extern char * get_imei();

extern void get_call_records(const char* imei, char** callRecords, int* recordCount);

extern int fd;







#endif
