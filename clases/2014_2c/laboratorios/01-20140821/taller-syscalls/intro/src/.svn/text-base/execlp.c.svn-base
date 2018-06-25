#include <stdio.h>
#include <unistd.h>

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
		printf("Soy el hijo\n");
	} else {
		/* Esto lo ejecuta sólo el padre. */
		printf("Yo soy el padre, mi hijo tiene pid %d.\n", pid);
	}
	
	return 0;
}
