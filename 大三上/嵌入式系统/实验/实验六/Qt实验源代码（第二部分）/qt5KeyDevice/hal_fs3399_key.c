#include "hal_fs3399_key.h"

int fd = 0;

void key_init(){
      fd = open(KEYS_PATH,O_RDWR);
      if(fd < 0){
          perror("open farsight_keys failed");
      }
}

int get_keys_clicked() {
    int buf[2] = {0};
    int err = 0;
    err = read(fd,buf,sizeof(buf));
    if(err > 0){
        if(buf[0] == 1){
            if(buf[1] == 0){
                return KEY1_ON;
            }else{
                return KEY1_OFF;
            }
        }else if(buf[0] == 2){
            if(buf[1] == 0){
                return KEY2_ON;
            }else{
                return KEY2_OFF;
            }
        }
    }else{
        return -1;
    }
}

int key_close()
{
    return close(fd);
}
