#include<stdio.h>
#include<termios.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
int main()
{
    struct termios tty;
    int Serial_port;
    char portname[20] = "/dev/ttyUSB0";
    Serial_port = open(portname,O_RDWR);
    if(Serial_port == -1) {
        printf("Error in opening serial port\n");
        return 1;
    }
    memset(&tty, 0, sizeof(tty));
    if(tcgetattr(Serial_port,&tty) != 0) {
        printf("Error in getting info about serial port\n");
        close(Serial_port);
        return 1;        
    }
    cfsetospeed(&tty, B2400);
    cfsetispeed(&tty, B2400);

    tty.c_cflag |= (CLOCAL | CREAD);
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;
    tty.c_cflag &= ~PARENB;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CRTSCTS;

    tty.c_lflag  = 0;
    tty.c_oflag  = 0;  

    tty.c_cc[VMIN] = 0;
    tty.c_cc[VTIME] = 5;

    if(tcsetattr(Serial_port,TCSANOW,&tty) != 0) {
        printf("Error in setting values to serial port\n");
        close(Serial_port);
        return 1;        
    }

    char data[] = "Finance Minister Arun Jaitley Tuesday hit out at former RBI governor Raghuram Rajan for predicting that the next banking crisis would be triggered by MSME lending, saying postmortem is easier than taking action when it was required. Rajan, who had as the chief economist at IMF warned of impending financial crisis of 2008, in a note to a parliamentary committee warned against ambitious credit targets and loan waivers, saying that they could be the sources of next banking crisis. Government should focus on sources of the next crisis, not just the last one.In particular, government should refrain from setting ambitious credit targets or waiving loans. Credit targets are sometimes achieved by abandoning appropriate due diligence, creating the environment for future NPAs, Rajan said in the note.Both MUDRA loans as well as the Kisan Credit Card, while popular, have to be examined more closely for potential credit risk. Rajan, who was RBI governor for three years till September 2016, is currently."

    char received_string[1000];

    int w = write(Serial_port, data, sizeof(data));
    if(w == -1 ) {
        printf("Error in sending data\n")
        return 1;
    }

    usleep(1000000);

    int r = read(Serial_port, received_string, sizeof(received_string))
    if(r == -1) {
        printf("Error in recieving data\n");
        return 1;
    }
    printf("REcieved string from arduino is : %s\n",received_string);
    
    close(Serial_port);
    return 0;

}
