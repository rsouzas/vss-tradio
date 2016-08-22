#include <fcntl.h>
#include <termios.h>
#include <sys/ioctl.h>

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void iniciaComunicacao(void);

void enviaDadosR(int);

void terminaComunicacao(void);
