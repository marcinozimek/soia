#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

key_t klucz = 3421673;
const int max_rozm = 100;

int main()
{ 
	srand(time(NULL));
	char* tab;
	int shmid = shmget(klucz, max_rozm, IPC_CREAT | 0600);
	printf("SchmID:%d\n ", shmid);
	if(shmid!=-1)
	{
		tab = shmat(shmid, NULL, 0);
		if(tab==0)
		{
		printf("Blad shmat\n");
			exit(0);
		}
		printf("Wysylanie\n");
		int i=0;
		
		while(1)
		{
			i%=max_rozm; 
			if(tab[i]==-1)
			tab[i]=rand()%10+48;
			i++;
		}
	}
	else
		printf("Blad shmget\nKoniec pobierania i wysylania\n");
		exit(0);
}
