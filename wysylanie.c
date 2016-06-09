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
const int max_rozm = 40;

int main(int argc, char** argv)
{ 
	
	srand(time(NULL));
	char* tab;
	unsigned long long ost=atoll(argv[1]);
	int a=atoi(argv[2]);	
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
		tab[0]=-1;
		printf("\nPierwszy wyraz ciagu: %llu\nIloraz ciagu geom: %d\n", ost, a);
		printf("tab:%d", tab[0]); 
		do{
			if(tab[0]==-1)
			{
				unsigned long long pet=ost;
				if(pet>(ost=ost*a))
					ost=0;
					memset(tab, 0, max_rozm);
					snprintf(tab,max_rozm, "%llu", ost);
			}
			else usleep(100);	
		}while(1);
	}
	else
		printf("Blad shmget\nKonciec pobierania i odbierania\n");
		exit(0);
}
