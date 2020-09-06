#include <stdio.h>
int main () {
	int *q = malloc(10*sizeof(int));
	int *r = malloc(10*sizeof(int));

	int *p = q;
	int *s;
	for(int i = 0; i < 1000000;i++)
		p[i] = i*i; 					//Out of bound write 

	printf("%d\n", q[1024]); 			//Out of bound read 
	free(p);
	free(q); 							//Double -free free(r);
	free(s); 							//Invalid free
	r[0] = 101; 						//Write after free 
	for(int i = 0; i < 100;i++)
		p[i] = i; 						//Write after free
	printf("%d\n", p[0]); 				//Read after free 
}