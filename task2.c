#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define TRUE  1
#define FALSE 0

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
  
    	if (x == 1  || x == _n-1) 
       		return TRUE; 
  
    	while (_d != _n-1) { 
        	x = (x * x) % _n; 
        	_d *= 2; 
  
        	if (x == 1)      
			return FALSE; 
        	if (x == _n-1)    
			return TRUE; 
    	} 
  
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
    	while (d % 2 == 0) 
        	d /= 2; 
			printf("while (d mod 2 == 0)  d = %ld\n", *&d);
  

    	for (long i = 0; i < _k; i++) { 

			printf("i = %ld, _k = %ld\n", i, _k);
        	if (!millerRabinTest(d, _n)) 
              		return FALSE; 
    	}
  
    	return TRUE; 
} 
  
int main(int argc, char** argv) { 
    	int numberOfThreads = 10; 
  
    	printf("Prime test \nPress -1 for quit\n"); 

	long buf;
	while (TRUE) {
		printf("Enter number: ");
		scanf("%ld", &buf);

		if(buf == -1)
			break;

       		if (isPrime(buf, numberOfThreads)) 
          		printf("%ld is prime\n\n\n", buf); 
		else
          		printf("%ld is not prime\n\n\n", buf); 
	}

  
    	return 0; 
} 
