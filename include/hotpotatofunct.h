#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define TOKEN nproc
#define PLAYERS nproc+1
#define TURN nproc+2
#define START nproc+3

void usage();
int get_token(int, char **);