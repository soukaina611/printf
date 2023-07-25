#include "main.h"

void print_buffer(char buffer[], int *buffer_i);

/**
 * _printf - function print string
 * @format: format string.
 * Return: Number of chars.
 */
int _printf(const char *format, ...)
{
	int index, printed_char = 0, sum_chars = 0;
	int buffer_i, flags, width, precision, size = 0;
	char buffer[BUFF_SIZE];
	va_list arguments;

	if (format == NULL)
		return (-1);
	va_start(arguments, format);
	for (index = 0; format && format[index] != '\0'; index++)
	{
		if (format[index] != '%')
		{
			buffer[buffer_i++] = format[index];
			if (buffer_i == BUFF_SIZE)
				print_buffer(buffer, &buffer_i);
			/* write(1, &format[index], 1);*/
			sum_chars++;
		}
		else
		{
			print_buffer(buffer, &buffer_i);
			flags = get_flags(format, &index);
			width = get_width(format, &index, arguments);
			size = get_size(format, &index);
			precision = get_precision(format, &index, arguments);
			++index;
			printed_char = handle_print(format, &index, arguments, buffer,
				flags, width, precision, size);
			if (printed_char == -1)
				return (-1);
			sum_chars += printed_char;
		}
	}

	print_buffer(buffer, &buffer_i);

	va_end(arguments);

	return (sum_chars);
}

/**
 * print_buffer - function that prints contents of buffer
 * @buffer: Array of characters
 * @buffer_i: Index to add next character
 */
void print_buffer(char buffer[], int *buffer_i)
{
	if (*buffer_i > 0)
		write(1, &buffer[0], *buffer_i);

	*buffer_i = 0;
}

