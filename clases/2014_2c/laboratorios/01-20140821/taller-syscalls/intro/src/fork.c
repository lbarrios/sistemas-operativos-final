#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	int pid;

	/* Crear un proceso. */	
	pid = fork();
	if (pid == -1)
		perror("creando proceso hijo");

	if (pid == 0) {
		/* Esto lo ejecuta sólo el hijo. */
		printf("Yo soy el hijo.\n");
	} else {
		/* Esto lo ejecuta sólo el padre. */
		printf("Yo soy el padre, mi hijo tiene pid %d.\n", pid);
	}
	
	return 0;
}
