/**********************function handle_print *******************/
#include "main.h"
/**
 * handle_print - function prints arguments depending on it's type
 * @fmt: format string of printed arguments
 * @arguments:  the list of arguments
 * @index: index
 * @buffer: the buffer array
 * @flags: the flags specifier
 * @width: the width given
 * @precision: the precision specification
 * @size: the size of specifier
 * Return:  the value 1 or 2
 */
int handle_print(const char *fmt, int *index, va_list arguments, char buffer[],
	int flags, int width, int precision, int size)
{
	int print_characters = -1, lenght = 0, j;
	fmt_t fmt_types[] = {
		{'c', print_char}, {'s', print_string}, {'%', print_percent},
		{'i', print_int}, {'d', print_int}, {'b', print_binary},
		{'u', print_unsigned}, {'o', print_octal}, {'x', print_hexadecimal},
		{'X', print_hexa_upper}, {'p', print_pointer}, {'S', print_non_printable},
		{'r', print_reverse}, {'R', print_rot13string}, {'\0', NULL}
	};
	for (j = 0; fmt_types[j].fmt != '\0'; j++)
		if (fmt[*index] == fmt_types[j].fmt)
			return (fmt_types[j].fn(arguments, buffer, flags, width, precision, size));

	if (fmt_types[j].fmt == '\0')
	{
		if (fmt[*index] == '\0')
			return (-1);
		lenght += write(1, "%%", 1);
		if (fmt[*index - 1] == ' ')
			lenght += write(1, " ", 1);
		else if (width)
		{
			--(*index);
			while (fmt[*index] != ' ' && fmt[*index] != '%')
				--(*index);
			if (fmt[*index] == ' ')
				--(*index);
			return (1);
		}
		lenght += write(1, &fmt[*index], 1);
		return (lenght);
	}
	return (print_characters);
}

