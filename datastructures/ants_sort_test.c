#include <ants_sort.h>
#include <stdio.h>


int arr_test[10] = {1, 10, -1, 20, 200, 2, 3, 5, 0, 44};

int main()
{
	int i = 0;
	quick_sort(arr_test, 0, 9);
	for (i=0; i<10; i++)
	{
		printf("%d ", arr_test[i]);
	}
	
	return 0;
}

