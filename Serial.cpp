#include "Serial.h"

const char *device = "/dev/ttyUSB0";
//const char *device = "/dev/ttyACM0";

struct termios cfg;

int fd = 0;

void erro(char *s) {
	perror(s);
	exit(0);
}

void iniciaComunicacao(void) {
	fd = open(device, O_RDWR | O_NOCTTY | O_NDELAY);
	if (fd == -1) {
		erro("erro na abertura da interface serial\n");
	}

	if (!isatty(fd)) {
		erro("A interface serial aberta nao é realmente uma interface serial!\n");
	}

	if (tcgetattr(fd, &cfg) < 0) {
		erro("A configuracao da interface serial nao pode ser lida!\n");
	}

	cfg.c_iflag = IGNBRK | IGNPAR;
	cfg.c_oflag = 0;
	cfg.c_lflag = 0;
	cfg.c_cflag = B115200 | CS8;// | CRTSCTS;// | CSTOPB;
	cfg.c_ispeed = 115200;
	cfg.c_ospeed = 115200;

	cfg.c_cc[VMIN] = 1;
	cfg.c_cc[VTIME] = 0;

//	int sercmd = 0;// desliga os bits TIOCM_RTS | TIOCM_DTR para colocar 12V na saida
//	ioctl(fd, TIOCMBIC, &sercmd); // Set the RTS pin.

	if (tcsetattr(fd, TCSAFLUSH, &cfg) < 0) {
			erro("A configuracao da interface serial nao pode ser alterada!\n");
		}

	if (cfsetispeed(&cfg, B115200) < 0 || cfsetospeed(&cfg, B115200) < 0) {
		erro("A interface serial nao pode ser configurada!\n");
	}
}

void enviaDadosR(int op) {
	tcflush(fd, TCIOFLUSH);
	unsigned char b[8];

	b[0] = 0x80;
	write(fd, b, 1);

	if(op ==1){
	// ENVIA PARA OS 3 ROBÔS 1 nas duas rodas
	b[0] = 1 << 4;    //0x7 << 4;
	b[1] = 1 << 4;    //0x7 << 4;
	b[2] = 1 << 4;    //0x7 << 4;
	b[3] = 1 << 4;    //0x7 << 4;
	b[4] = 1 << 4;    //0x7 << 4;
	b[5] = 1 << 4;    //0x7 << 4;
	b[6] = '0';
	b[7] = '0';
    }

    if(op == 2){
	// ENVIA PARA OS 3 ROBÔS 1 na roda direita
	b[0] = 1 << 4;    //0x7 << 4;
	b[1] = 0 << 4;    //0x7 << 4;
	b[2] = 1 << 4;    //0x7 << 4;
	b[3] = 0 << 4;    //0x7 << 4;
	b[4] = 1 << 4;    //0x7 << 4;
	b[5] = 0 << 4;    //0x7 << 4;
	b[6] = '0';
	b[7] = '0';
    }

    if(op == 3){
	// ENVIA PARA OS 3 ROBÔS 1 na roda esquerda
	b[0] = 0 << 4;    //0x7 << 4;
	b[1] = 1 << 4;    //0x7 << 4;
	b[2] = 0 << 4;    //0x7 << 4;
	b[3] = 1 << 4;    //0x7 << 4;
	b[4] = 0 << 4;    //0x7 << 4;
	b[5] = 1 << 4;    //0x7 << 4;
	b[6] = '0';
	b[7] = '0';
    }

    if(op == 0){
	// ENVIA PARA OS 3 ROBÔS 0 nas duas rodas
	b[0] = 0 << 4;    //0x7 << 4;
	b[1] = 0 << 4;    //0x7 << 4;
	b[2] = 0 << 4;    //0x7 << 4;
	b[3] = 0 << 4;    //0x7 << 4;
	b[4] = 0 << 4;    //0x7 << 4;
	b[5] = 0 << 4;    //0x7 << 4;
	b[6] = '0';
	b[7] = '0';
    }


	int resp = write(fd, b, 8);

	if (resp < 0) {
		erro("Interface serial - nao pode enviar comandos aos robos.\n");
	}
}

void terminaComunicacao(void) {
	int sercmd = TIOCM_RTS | TIOCM_DTR;
	ioctl(fd, TIOCMBIC, &sercmd);
	close(fd);
}
