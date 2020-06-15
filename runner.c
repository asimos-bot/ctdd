#include "test.h"
//#include <ctdd/ctdd.h>
#include "ctdd.h"

#include <string.h>

int test__double(){

	ctdd_assert(_double(1)==4);
	return 0;
}

int test_sigsegv(){

	char buf[10]="hello";

	memcpy(0, buf, 10000);

	return 0;
}

int run_tests(){

	ctdd_verify(test__double);
	ctdd_verify(test_sigsegv);
	return 0;
}

int main(){

	ctdd_setup_signal_handler();

	ctdd_results(run_tests);

	return 0;
}
