#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
pid_t wysylanie, odbieranie;

if((odbieranie=fork())==0)
	{	
		execl("./odbieranie", "NULL", NULL);
		printf("Blad execl odbierania\n");
		_exit(EXIT_FAILURE);
	}
else
	if(odbieranie==-1)
	{
		perror("Blad fork odbierania");
		exit(EXIT_FAILURE);
	}
	
if((wysylanie=fork())==0)
{		
	execl("./wysylanie", "NULL", NULL);
	printf("Blad wysylania w execl\n");
	exit(EXIT_FAILURE);
}
else
	if(wysylanie==-1)
	{
		perror("Blad fork wysylania");
		exit(EXIT_FAILURE);
	}
	int status=0;
	if(wait(&status)==-1)
		printf("Blad wait()\n");
	else
	{
		if(WIFEXITED(status)&&WEXITSTATUS(status))
		{
			printf("Odbieranie zatrzymane. Koniec wysylania\n");
			kill(wysylanie, SIGTERM);
		}
	}	

printf("Wysylanie i pobieranie zakonczone\n");
exit(0);
}
