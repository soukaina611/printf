/******************************function get_widh****************************/
#include "main.h"

/**
 * get_width - func that calculates the width
 * @format: format string
 * @p: the list of arg to be printed
 * @arguments: the list of arguments
 * Return: the width
 */
int get_width(const char *format, int *p, va_list arguments)
{
	int width = 0;
	int current_p;

	for (current_p = *p + 1; format[current_p] != '\0'; current_p++)
	{
		if (is_digit(format[current_p]))
		{
			width *= 10;
			width += format[current_p] - '0';
		}
		else if (format[current_p] == '*')
		{
			current_p++;
			width = va_arg(arguments, int);
			break;
		}
		else
			break;
	}

	*p = current_p - 1;

	return (width);
}

