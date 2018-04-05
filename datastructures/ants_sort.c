#ifndef _ANTS_SORT_
#define _ANTS_SORT_


void quick_sort(int arr[], int left, int right)
{
	int i, j, pivot;
	int temp;
	
	i = left;
	j = right;
	pivot = arr[(left + right) / 2];

	do
	{
		while (arr[i] < pivot)
			i++;

		while (arr[j] > pivot)
			j--;

		if ( i <= j )
		{
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
			i++;
			j--;
		}
	} while (i<=j);

	if (left < j)
		quick_sort(arr, left, j);

	if (i < right)
		quick_sort(arr, i, right);
}



#endif
