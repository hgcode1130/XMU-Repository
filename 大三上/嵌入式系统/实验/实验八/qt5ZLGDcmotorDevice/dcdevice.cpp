#include \
dcdevice.h\

dcDevice::dcDevice()
{
}

void dcDevice::initDc()
{
    dcfd = 0;
    dcfd = open(\/dev/dc_motor\, O_RDWR);
    if (dcfd < 0) {
        perror(\open\);
    }
}

void dcDevice::controlDc(int operation)
{
    switch (operation) {
    case 0:
        ioctl(dcfd, DC_MOTOR_ON);
        ioctl(dcfd, DC_MOTOR_DIR, &operation);
        break;
    case 1:
        ioctl(dcfd, DC_MOTOR_ON);
        ioctl(dcfd, DC_MOTOR_DIR, &operation);
        break;
    case 2:
        ioctl(dcfd, DC_MOTOR_OFF);
        break;
    }
}

void dcDevice::closeDc()
{
    if (dcfd > 0) {
        close(dcfd);
        dcfd = 0;
    }
}

dcDevice::~dcDevice()
{
    closeDc();
}
