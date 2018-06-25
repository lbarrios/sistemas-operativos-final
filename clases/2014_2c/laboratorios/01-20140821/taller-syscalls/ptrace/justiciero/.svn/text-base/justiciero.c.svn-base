#include <stdlib.h>
#include <stdio.h>
#include <sys/ptrace.h>
//#include <sys/user.h>
#include <sys/reg.h>

//char syscall_names[256][256];
//#define __SYSCALL(a,b) strcpy( syscall_names[a], #b );
//#include <asm/unistd_64.h>



int main(int argc, char const *argv[])
{
	int child = fork();
	int status;
	long signo;

	if (child == -1) 
	{ 
		perror("ERROR fork"); return 1; 
	}
	if (child == 0) 
	{
	/* Si lo ejecuta el Hijo */
		if (ptrace(PTRACE_TRACEME, 0, NULL, NULL))
		{
			perror("ERROR child ptrace(PTRACE TRACEME, ...)"); exit(1);
		}
		execvp(argv[1], argv+1);
		/* Si vuelve de exec() hubo un error */
		perror("ERROR child exec(...)"); exit(1);
	} else {
	/* Si lo ejecuta en el Padre */
		while(1) {
			if (wait(&status) < 0) { perror("wait err"); break; }
			if (WIFEXITED(status)) break; /* Proceso terminado */
			signo = ptrace(PTRACE_PEEKUSER, child, 8*ORIG_RAX, NULL);
			if(signo==62)
			{
				printf("hijo malo: %d, estado: %d, syscall: %ld\n", child, status, signo);
				printf("SE HA HECHO JUSTICIA!!!");
				kill(child);
				return 0;
			}
			ptrace(PTRACE_SYSCALL, child, NULL, NULL); /* contin ́a */
		}
		ptrace(PTRACE_DETACH, child, NULL, NULL);/*Liberamos al hijo*/
	}
	return 0;
}


//  gcc justiciero.c && ./a.out kill `ps | grep sleep | awk ' { print $1 } '`