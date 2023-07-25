#include "main.h"

/**
 * get_precision -  function that calculate the precision
 * @format: format string we want to print the argument
 * @arg: arguments to be printed
 * @arguments:  the list of arguments
 * Return: Precision
 */
int get_precision(const char *format, int *arg, va_list arguments)
{
	int current_arg = *arg + 1;
	int precision = -1;

	if (format[current_arg] != '.')
		return (precision);

	precision = 0;

	for (current_arg += 1; format[current_arg] != '\0'; current_arg++)
	{
		if (is_digit(format[current_arg]))
		{
			precision *= 10;
			precision += format[current_arg] - '0';
		}
		else if (format[current_arg] == '*')
		{
			current_arg++;
			precision = va_arg(arguments, int);
			break;
		}
		else
			break;
	}

	*arg = current_arg - 1;

	return (precision);
}

