#include "hotpotatofunct.h"

void usage(){
	printf("usage: hotpotato -t input token\n");
	printf("\t\t-h (Display this message)\n");
}

int get_token(int argc, char *argv[]){
	if (argc < 3){
		usage();
		exit(1);
	}
	int token;
	int gopt;
	while((gopt = getopt(argc, argv, "t:h") ) != -1)
		switch(gopt){
			case 'h':
				usage();
				exit(1);
			case 't':
				token = atoi(optarg); 
				break;
			default:
				abort();
		}
	return token;
}