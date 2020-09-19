#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>
#include <math.h>


#define TRUE  1
#define FALSE 0

    int world_size;

    int world_rank;

int already_passed = 0;

int repeatedSquare(long _b, unsigned int _e, int _m) {
    	long res = 1;
	_b = _b % _m;

    	if (_b == 0) 
		return 0;

    	while (_e > 0) {
        if (_e & 1)
            	res = (res*_b) % _m;

        	_e /= 2;
        	_b = (_b*_b) % _m;
    	}
    	return res;
}

int millerRabinTest(long _d, long _n) { 

		printf("Miller-Rabin   ->  %ld   %ld\n", *&_d, *&_n);

    	long a = 2 + rand() % (_n - 4); 
  
    	long x = repeatedSquare(a, _d, _n); 
  
    	if (x == 1  || x == _n-1) {
			already_passed = 1;
            MPI_Send(&already_passed, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
       		return TRUE;
		} 
  
    	while (_d != _n-1) { 
        	x = (x * x) % _n; 
        	_d *= 2; 

			printf("MR  x = %ld, _d = %ld\n", x, _d);
  
        	if (x == 1)  {    

                printf("MR returning FALSE 55\n");
			    return FALSE; 
            }
        	if (x == _n-1)  {
				already_passed = 1;
                MPI_Send(&already_passed, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
       		    return TRUE; 
			}  
    	} 
  
        printf("MR returning FALSE 65\n");
    	return FALSE; 
} 
  
   
int isPrime(long _n, long _k) { 



    	if (_n <= 1 || _n == 4)  
		return FALSE; 
    	if (_n <= 3) 
		return TRUE; 
  
    	long d = _n - 1; 
		printf("n = %ld\n", *&_n);
		printf("long d = _n - 1;  ->   d = %ld\n", *&d);
    	while (d % 2 == 0) {
        	d /= 2; 
			printf("while (d mod 2 == 0)  d = %ld\n", *&d);	
		}
  

    	for (long i = 0; i < _k; i++) { 

			// printf("i = %ld, _k = %ld\n", i, _k);
        	if (!millerRabinTest(d, _n)) 
              		return FALSE; 
    	}


    	return TRUE; 
} 


int main() { 


	// Initialize the MPI environmen
    MPI_Init(NULL, NULL);
        // Get the number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

	int numberOfThreads = 5; 


	long buf;
        // printf("Enter number: ");
        scanf("%ld", &buf);
        printf("Entered number %ld\n", buf);
        already_passed = 0;
        // printf("Hello world rank %d out of %d processors\n",
        //    world_rank, world_size);

           if (isPrime(buf, numberOfThreads))
          		printf("%ld is prime\n\n\n", buf); 
            else
          		printf("%ld is not prime\n\n\n", buf); 

	


    // Finalize the MPI environment.
    MPI_Finalize();
		
    return 0; 
} 
 