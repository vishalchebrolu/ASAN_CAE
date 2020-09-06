#include <stdio.h>

int main () {
	int *p = malloc(100*sizeof(int));
	int *q = malloc(500*sizeof(int)); 
	int *r;

	int n;
	scanf("%d", &n); 
	if(n > 1)
		r = p;
	else
		r = q;

	r[150] = 1; // Weak update 
	if(n > 0)
		free(p);
	else
		free(q);

	free(r); 	// Can lead to double -free
}