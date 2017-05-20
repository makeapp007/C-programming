#include <stdio.h>
#include <stdlib.h>

// static data
int a;
int b;
int c;
int d=1;
// int e[1000000]={1}; //if initialized, it will cost huge amounts of storage.(hundreds of MB)
int f[1000000];  //uninitialized variable. only cost several KBs.


int foo(){
	int temp = 10;
	printf("%p\n", &temp); //0x7fff5afd88fc. since this value is determined when program is running, 
						   //main function will be stored in stack first, then is foo()
}
int main(int argc, char const *argv[])
{

	char* x = "Hello World";
	char y[]= "Hello World";
	// x[1] = 'X';  //read-only. because sizeof(x) gets the size of pointer, it does not know which location is ok to modify
	y[1] = 'X';    //can write, corresponding data is copied to stack. since sizeof(y) gets number of elements

	printf("%p\n", &a); //0x109fdd040
	printf("%p\n", &b); //0x109fdd044
	printf("%p\n", &c); //0x109fdd048
	printf("%p\n", &d); //0x109fdd018. this is a gap between initialized data and uninitialized data for static data

	printf("%p\n", x);  //0x109fdcf66
	printf("%p\n", y);  //0x7fff5afd8930 
	printf("%ld\n", sizeof(x)); // on 64 bit machine,8
	printf("%ld\n", sizeof(y)); // 12
	int *p = (int *)  malloc (sizeof(int));
	printf("%p\n", p);  //0x7fc13ac03160  this value is the address of a chunk of data on heap. it is smaller than any address on the stack.
	printf("%p\n", &p); //0x7fff5afd8928  it is p's address. it is on stack.

	foo();
	printf("%p\n", f);
	printf("%p\n", &f[0]);
	printf("%p\n", &f[1]);

	sleep(10);
	int i=0;
	for(i=0;i<1000000;i++){
		f[i]=i;
	}

	printf("%p\n", f);
	printf("%p\n", &f[0]);
	printf("%p\n", &f[1]);
	sleep(100);
	// check static data

	return 0;
}