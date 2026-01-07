#include "hal_c_msg.h"

int fd = 0;

void set_callphone()
{
    int nwrite;
    int simwrite = write(fd,GET_SIM,strlen(GET_SIM));
    if(simwrite <= 0)
    {
        perror("faile to write GET_SIM");
    }
    if((nwrite = write(fd, SET_CALL, strlen(SET_CALL))) <= 0)
    {
      perror("fail to write SET_CALL");
    }
    else{
        printf("set call over\n");
    }

}

char *get_imei()
{
    char *imei_buf = (char*)malloc(100 * sizeof(char));
//    char *buf = NULL;
    int nwrite, nread;
//    char phone[20] = {0};
    tcflush(fd, TCIOFLUSH);

    if ((nwrite = write(fd, GET_PHONENUM, strlen(GET_PHONENUM))) <= 0) {
      perror("fail to write GET_PHONENUM");
      free(imei_buf); // 如果写入失败，释放内存
      return "-1";
    }

    usleep(100000);
        char* start = strstr(imei_buf, "\r\n");
        if (start != NULL) {
        start += 2;
        char* end = strstr(start, "\r\n");
        if (end != NULL) {
          *end = '\0';
          free(imei_buf);
          return start;
        }
        }
//    }
}

/*波特率选择函数*/
int baud_choose(int baud)
{
    int baudrates;

    switch(baud){
    case 0: baudrates = B0; break;
    case 9600: baudrates = B9600; break;
    case 19200: baudrates = B19200; break;
    case 38400: baudrates = B38400; break;
    case 57600: baudrates = B57600; break;
    case 115200: baudrates = B115200; break;
    default : baudrates = -1;
    }

    return baudrates;
}

/*设备文件串口属性设置函数*/
int tty_usb_set(int fd, int baud, int size)
{
    int baudrates;
    int csx;
    struct termios old_attr, new_attr;

    tcgetattr(fd, &old_attr);
    new_attr = old_attr;

    if(-1 == (baudrates = baud_choose(baud))){
        printf("no baudrates you wanted, default option: 115200\n");
        baudrates = B115200;
    }

    cfsetispeed(&new_attr , baudrates);  //设置串口的输入/输出波特率。一般情况下输入和输出波特率相等的
    cfsetospeed(&new_attr , baudrates);
    new_attr.c_cflag |= (CLOCAL | CREAD);

    switch(size){
    case 5: csx = CS5; break;
    case 6: csx = CS6; break;
    case 7: csx = CS7; break;
    default : csx = CS8; break;
    }

    new_attr.c_cflag &= ~CSIZE;
    new_attr.c_cflag |= csx;
    new_attr.c_cflag &= ~CSTOPB;
    new_attr.c_cflag &= ~PARENB;
    new_attr.c_cflag &= ~CRTSCTS;
    new_attr.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    new_attr.c_iflag |= (IXON | IXOFF | IXANY);
    new_attr.c_oflag &= ~OPOST;
    //	new_attr.c_cc[VMIN]  = LEN;
    //	new_attr.c_cc[VTIME] = 200; //2s

    if( -1 == tcsetattr(fd , TCSANOW , &new_attr)){   //激活配置
        perror("set ttyusbx error");
        exit(EXIT_FAILURE);
    }
    return 0;
}

int tty_usb_open() {
      fd = open("/dev/ttyUSB2", O_RDWR | O_NOCTTY);
      if(fd == -1)
      {
          sleep(1);
          printf("open ttyUSB2 error: %s\n", strerror(errno));
          return fd;
      }
      tty_usb_set(fd, 115200, 8);
//    open_and_check_imei();

    set_callphone();
    return fd;

}


int string_compare(char ch1[Num])
{
    char *p;
    p = ch1;
    while(*p != '\0')
    {
        if((*p == 'O') && ((*(p + 1)) == 'K') )
        {
            return 1;
        }
        else
        {
            p++;
        }
    }
    return 0;
}


int gprs_option_handle(char *phone_num)
{
    printf("%s\n",phone_num);
    if(fd == -1)
    {
        return 0;
    }
    int nread;
    int  nwrite;
    char CALL_NUM[16];
    char temp_buf[32];
    sprintf(CALL_NUM , "ATD%s;\r" , phone_num);

    if((nwrite = write(fd , CALL_NUM , strlen(CALL_NUM))) <= 0)
    {
        perror("fail to write CALL_NUM");
    }
    usleep(100);

    memset(temp_buf, 0, sizeof(temp_buf));
    return 0;
}

int handup()
{
//    int nread;
    int  nwrite;
//    char temp_buf[32];
    if((nwrite = write(fd , HAND_UP , strlen(HAND_UP))) <= 0)
    {
        perror("fail to write HAND_UP");
    }

    if((nwrite = write(fd , NOWAITHAND_UP , strlen(NOWAITHAND_UP))) <= 0)
    {
        perror("fail to write NOWAITHAND_UP");
    }

    return 0;
}

// 判断结束标识函数
int is_end_of_data(char* buf) {

  // 判断是否包含"+CLIP: "开头
    if(strstr(buf, "+CLIP: ")) {

  // 查找号码字符串结束的双引号
    char* end = strchr(buf, '"');

  // 结束位置不为空则表示读到完整号码
    if(end != NULL) {
      return 1;
    }

  }

  return 0;

}

char* get_callphone() {
    if(fd == -1)
    {
        return "modellost";
    }
    char buf[100];
    int nwrite, nread;


    if((nwrite = write(fd, GET_CALL, strlen(GET_CALL))) <= 0) {
      perror("fail to write GET_CALL");
      return NULL;
    }

    usleep(10000);

    char phone[20];
    int Value=0;
    char* cme = NULL;
    char* clip_start = NULL;
    char* colp_start = NULL;
    char* no_carrier = NULL;
    int stateChar = 0;

    while(1) {
      nread = read(fd, buf, sizeof(buf));
//    if(nread <= 0) {
//        perror("Read failed");
//        break;
//      }
      //printf("buf:%s\n",buf);
      cme = strstr(buf, "+CME ERROR:");
      clip_start = strstr(buf, "+CLIP:");
      colp_start = strstr(buf, "+COLP:");
      no_carrier = strstr(buf, "NO CARRIER");
      if(cme != NULL)
      {
          if(sscanf(cme, "+CME ERROR: %d", &Value) == 1) {
              return "ERROR";
          }
      }

    if(clip_start != NULL) {
          //1=CLIP
          stateChar = 1;
          printf("clip_start:%s\n",clip_start);
          if(sscanf(clip_start, "+CLIP: \"%[^\"]\",%d", phone, &Value) == 2) {
              printf("phone:%s\n",phone);
              printf("Value:%d\n",Value);
              break;
        }
      }

    if(colp_start != NULL) {
        //2=COLP
        stateChar = 2;
        printf("buf:%s\n",buf);
        printf("colp_start:%s\n",colp_start);
          if(sscanf(colp_start, "+COLP: \"%[^\"]\",%d", phone, &Value) == 2) {

            printf("phone:%s\n",phone);
            printf("Value:%d\n",Value);
              break;
        }
      }

    if(no_carrier != NULL) {
          return "nocarrier";
      }
    }
    if(((stateChar == 1) && (Value == 129))||(Value == 128)) {
      char* ret = malloc(20);
      strcpy(ret, phone);
      printf("ret:%s\n",ret);
      return ret;
    } else if(((stateChar == 2) && (Value == 129))) {
      return "Answer";
    } else {
      return NULL;
    }
}

int answer_thephone()
{
    int  nwrite;
    if((nwrite = write(fd , ANSWER , strlen(ANSWER))) <= 0)
    {
        perror("fail to write ANSWER");
    }

    return 0;
}
