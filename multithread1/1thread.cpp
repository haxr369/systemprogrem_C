#include <stdio.h>

int pN(int n);
int main() {

	int i = 0;
	while (i<=10) {
		pN(i);
		i++;
	}
}

int pN(int n) {

	int i;
	for (i = 0; i < 5; i++)
		printf("%d%d%d%d%d%d%d%d\n", n, n, n, n, n, n, n, n);
	return 0;
}