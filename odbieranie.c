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
const int max_ciag = 5;

void tabela(void);

int main()
{
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
			printf("Blad shmat!\n");
			exit(0);
		}
		int i, licznik=0;	
		printf("Stan odbierania: Pracuje\nWartosci tabeli:\n");
		tabela();	
		time_t start=time(NULL);
		do
		{
			printf("\r|");
			for(i=1;i<max_rozm+1;i++)
			{
				if(tab[i]!=tab[i-1] || tab[i]==-1)
					licznik=0;
				else
					licznik++;
			printf("%c |",tab[i-1]);
			if(i>=2)
				tab[i-2]=-1;
			if (licznik==max_ciag)
				break;
			}
			tab[max_rozm-1]=-1;
			tab[max_rozm-2]=-1;
		}
		while(licznik<max_ciag);
		printf("\nZnaleziono %d takich bajtow w %d sekund\nKoniec pracy odbierania i pobierania\n", max_ciag, (int)(time(NULL)-start));
		exit(1);
	}
	else
		printf("Blad shmget\nKoniec odbierania\n");
	exit(0);
}
void tabela(void)
{
	int t;
	for(t=0;t<max_rozm;t++)
	{
		if(t<10)
			printf("|%d ",t);
		else
			printf("|%d",t);
	}
	printf("|\n");
}
