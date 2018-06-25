#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>


int main() {
	int pid;

	/* Crear un proceso. */	
	pid = fork();
	if (pid == -1)
		perror("creando proceso hijo");
		
	if (pid == 0) {
		/* Esto lo ejecuta sólo el hijo. */
		if (execlp("/bin/ls", "ls", "-l", NULL) == -1)
			perror("haciendo exec");
	} else {
		/* Esto lo ejecuta sólo el padre. */
		printf("Yo soy el padre, mi hijo tiene pid %d.\n", pid);

		/*Esperar a que el hijo termine antes de terminar. */
		printf("Acaba de terminar el proceso con pid == %d.\n",
			wait(NULL));
	}
	
	return 0;
}
