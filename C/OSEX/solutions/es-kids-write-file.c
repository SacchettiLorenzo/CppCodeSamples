#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

/*
#define NO_BUFFERING
*/

int main(int argc, char ** argv) {
	int n_kids, n_writes, i;
	FILE * f;

	if (argc < 4) {
		fprintf(stderr, "Not enough arguments\n");
		return -1;
	}

	if ((f = fopen(argv[1], "w")) == NULL) {
		fprintf(stderr, "Unable to open \"%s\"\n", argv[1]);	
		return -1;
	}
#ifdef NO_BUFFERING
	setvbuf(f, NULL, _IONBF, 0);
#endif
	if (!(n_kids = atoi(argv[2]))) {
		fprintf(stderr, "Please specify the second argument\n");
		return -1;
	}
	if (!(n_writes = atoi(argv[3]))) {
		fprintf(stderr, "Please specify the third argument\n");
		return -1;
	}
	for (i=0; i<n_kids; i++) {
		if (!fork()) {
			for (i=0; i<n_writes; i++) {
				fprintf(f,"%d,%d\n",getpid(),getppid());
			}
			break;
		}
	}
	fclose(f);
	return 0;
}
