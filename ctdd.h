#ifndef CTDD_H
#define CTDD_H

#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

long unsigned int ctdd_sucessful_tests=0;

#define ctdd_FAIL() printf("\n\x1b[31mfailure\x1b[0m in %s() line %d\n", __func__, __LINE__)

#define ctdd_assert(result) do { if (!(result)) { ctdd_FAIL(); return 1; } } while (0)

#define ctdd_verify(test) do { int r=test(); if(r) return r; else ctdd_sucessful_tests++; } while(0)

void ctdd_signal_handler(int signum){

	printf("\x1b[31mfailure\x1b[0m(%d) (\x1b[31mSIGSEGV\x1b[0m) - %lu tests ran sucessfully\n", signum, ctdd_sucessful_tests);
	exit(1);
}

void ctdd_setup_signal_handler(){

	struct sigaction sig={0};
	sig.sa_handler = ctdd_signal_handler;
	sigaction(SIGSEGV, &sig, NULL);
}

int ctdd_test(int (*test_runner)()){

	int r = test_runner();

	if( r ){
	
		printf("\x1b[31mfailure\x1b[0m - %lu tests ran sucessfully\n", ctdd_sucessful_tests);
	} else {

		printf("\x1b[32msucess\x1b[0m - all %lu tests ran sucessfully\n", ctdd_sucessful_tests);
	}

	return r;
}

#endif
