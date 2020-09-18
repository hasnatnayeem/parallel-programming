#include <stdio.h>
#include <math.h>
#include <omp.h>
 
int main(int argc, char** argv){
	long int N = 770948605618065980;
	printf("Number to be tested: %ld\n", N);
	long int upper = (long int) sqrt(N);
	omp_set_num_threads(2);
	#pragma omp parallel
	{
		int ID = omp_get_thread_num();
		int start,stop;
		if (ID == 0){
			start = 2;
			stop = 439018395;
		}
		else{
			start = 439018396;
			stop = upper;
		}
		for (long int j = start; j <= stop; j++){
			if (N%j == 0){
				printf("Factor found: %ld\n", j);
				break;
			}
		}
	}
	return(0);
}
