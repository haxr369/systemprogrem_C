#include <stdio.h>

int main() {


	int a = 10, b = 20, c = 30;
	a = b = c;
	
	while (a < 50) {

		printf("a= %d\n", a);
		a++;
	}
}
