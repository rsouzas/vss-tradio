#include <stdio.h>
#include <stdlib.h>
#include "Serial.h"


int main()
{
    int op = 0;

    iniciaComunicacao();

    while(op != 4)
    {

        printf("\n\n\n\tMENU\n1-TESTAR RADIO\n2-TESTAR MOTOR DIREITO PELO RADIO\n3-TESTAR MOTOR ESQUERDO PELO RADIO\n4-SAIR\nDigite sua opcao de teste: ");
        scanf("%i", &op);

        switch (op)
        {
            case 1: system("clear");
            		for(int i = 0; i<100; i++)
            		{
                        usleep(33333);
            			enviaDadosR(op);
                    }
                    break;
            case 2: system("clear");
                    for(int i = 0; i<100; i++)
            		{
                        usleep(33333);
            			enviaDadosR(op);
                    }
                    break;
            case 3: system("clear");
            		for(int i = 0; i<100; i++)
            		{
                        usleep(33333);
            			enviaDadosR(op);
                    }
                    break;
            case 4: exit(1);
                    break;
            default: system("clear");
                     printf("OPCAO INVALIDA, TENTE NOVAMENTE");
                     break;
        }
        enviaDadosR(0);

    }
    terminaComunicacao();
}
