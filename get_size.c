#include "main.h"

/**
 * get_size -  function that calculate size to cast arg
 * @format: format string we want to print the argument
 * @list: the list of arguments
 * Return: size
 */
int get_size(const char *format, int *list)
{
	int current_list = *list + 1;
	int size = 0;

	if (format[current_list] == 'l')
		size = S_LONG;
	else if (format[current_list] == 'h')
		size = S_SHORT;

	if (size == 0)
		*list = current_list - 1;
	else
		*list = current_list;

	return (size);
}
