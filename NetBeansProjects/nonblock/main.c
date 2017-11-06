#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // usleep
#include "nonblock.h"
#include <time.h>
#include "termlib.h"

#define T_MAX 300


#ifdef _WIN32
   #error "This program is only targeted at Linux systems"
#endif

int main(void) {
    char c;
    int rnum,gsnum,timecount;
	timecount=0;
	srand(time(NULL));
	rnum=rand()%10+1;
	gsnum=30;
        sleep(1);
    nonblock(NB_ENABLE);
    while(gsnum!=rnum)
    {
	printf("Quedan %d segundos\n", T_MAX-timecount);        
	if (kbhit())
		{
			c=getch();
                        if(c<'9'&&c>'0')
			{gsnum=(c-'0');
			printf("selected number=%d\n",gsnum);
			if(gsnum==rnum)
			printf("Ganaste amigo\n");
			else
			printf("La pifiaste intenta de nuevo, estoy seguro de que perderas\n");
                        }
                        else
                          printf("y si pones un numerito capo?\n");
        }

	timecount++;
	sleep(1);
	if(timecount==T_MAX)
	{
		printf("Dormiste amigo\n");	
		break;
	}
    }
    printf("El numero era %d\n", rnum);
    nonblock(NB_DISABLE);

    return 0;
}

