/**
* helpers.c
*
* Computer Science 50
* Problem Set 3
*
* Helper functions for Problem Set 3.
*/

#include <cs50.h>

#include "helpers.h"

/**
* Returns true if value is in array of n values, else false.
*/
bool search(int value, int values[], int n)
{
	if (n < 0) return false;
	int min = 0;
	int max = n - 1;
	while (min <= max)
	{
		int	middle = (min + max) / 2;
		if (values[middle] == value)
			return true;
		else if (values[middle] < value)
			min = middle + 1;
		else if (values[middle] > value)
			max = middle - 1;
	}
	return false;
}

/**
* Sorts array of n values.
*/
void sort(int values[], int n)
{
	for (int i = 0; i < n; ++i)
	{
		for (int j = i; j < n; ++j)
			if (values[i] > values[j])
			{
				int temp = values[i];
				values[i] = values[j];
				values[j] = temp;
			}
	}
	return;
}