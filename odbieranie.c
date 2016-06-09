#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

key_t klucz = 3421673;
const int max_rozm = 40;

int main(){
	printf("Odbieranie zaczyna prace!\n");
	size_t rozm=max_rozm;
	char* tab;
	int shmid;
	shmid = shmget(klucz, rozm*sizeof(char), IPC_CREAT | 0600);
	if(shmid!=-1)
	{
		tab = shmat(shmid, NULL, 0);
		if(tab==0)
		{
			printf("Blad shmat\n");
			exit(0);
		}
		int licznik=0;
		printf("Stan odbierania: pracuje\n");
		usleep(10000);
		do{
			if(tab[0]!=-1)
			{
				licznik++;
				printf("\nLicznik: %d\t Wartosc:%s", licznik, tab);
				if(tab[0]=='0')
				{
					printf("\rOsiagnieto maksymalna wartosc\n");
					break;
				}
				tab[0]=-1;
			}
			else usleep(100);	
		}while(1);
		printf("\nWychodzenie z wysylania i odbierania\n");
		exit(1);
	}
	else
		printf("Blad shmget\nKoniec odbierenia\n");
	exit(0);
}
