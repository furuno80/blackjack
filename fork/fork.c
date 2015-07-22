#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	pid_t child = fork();
	if(child == -1) {
		perror("Could not fork");
	} else if (child) {
		printf("New process is %d\n", child);
	}
 }
