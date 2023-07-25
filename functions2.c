#include "main.h"
/******************function print_pointer ******************/
/**
 * print_pointer - function that print val of ptr variable
 * @arguments: the list a of arguments
 * @buffer: the buffer array
 * @flags:  the flags specifier
 * @width: the given width
 * @precision: the precision secification
 * @size: the size
 * Return: value of pointer.
 */
int print_pointer(va_list arguments, char buffer[],
	int flags, int width, int precision, int size)
{
	char p_addr = '', c = 0;
	int index = BUFF_SIZE - 2, len = 2, p_addr_start = 1;
	unsigned long number_addr;
	char mapping_to[] = "0123456789abcdef";
	void *addr_s = va_arg(arguments, void *);

	UNUSED(width);
	UNUSED(size);

	if (addr_s == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);

	number_addr = (unsigned long)addr_s;

	while (number_addr > 0)
	{
		buffer[index--] = mapping_to[number_addr % 16];
		number_addr /= 16;
		len++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		p_addr = '0';
	if (flags & F_PLUS)
		c = '+', len++;
	else if (flags & F_SPACE)
		c = ' ', len++;

	index++;

	/*return (write(1, &buffer[i], BUFF_SIZE - i - 1));*/
	return (write_pointer(buffer, index, len,
		width, flags, p_addr, c, p_addr_start));
}

/*************************function print_non_printable***********************/
/**
 * print_non_printable - func print ASCII in hexa of non printable character
 * @arguments:  the list of arguments
 * @buffer:  the buffer array
 * @flags:  the flags specifier
 * @width: the width given
 * @precision: the precision specific
 * @size: the size of specifier
 * Return: non printable chars
 */
int print_non_printable(va_list arguments, char buffer[],
	int flags, int width, int precision, int size)
{
	int  balance = 0, ind = 0;
	char *string = va_arg(arguments, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (string == NULL)
		return (write(1, "(null)", 6));

	while (string[ind] != '\0')
	{
		if (is_printable(string[ind]))
			buffer[ind + balance] = string[ind];
		else
			balance += append_hexa_code(string[ind], buffer, ind + balance);

		ind++;
	}

	buffer[ind + balance] = '\0';

	return (write(1, buffer, ind + balance));
}

/*************************function print_reverse*************************/
/**
 * print_reverse - Function that print a reverse string
 * @arguments: the list of arguments
 * @buffer: The buffer array
 * @flags:  the flags specifier
 * @width: the width given
 * @precision:  the precision specification
 * @size: the size of specifier
 * Return: a reverse string
 */

int print_reverse(va_list arguments, char buffer[],
	int flags, int width, int precision, int size)
{
	char *string;
	int ind, counter = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	string = va_arg(arguments, char *);

	if (string == NULL)
	{
		UNUSED(precision);

		string = ")Null(";
	}
	for (ind = 0; string[ind]; ind++)
		;

	for (ind = ind - 1; ind >= 0; ind--)
	{
		char c = string[ind];

		write(1, &c, 1);
		counter++;
	}
	return (counter);
}
/*************************print_rot13 *************************/
/**
 * print_rot13string - function that print a string in rot 13
 * @arguments: the list of arguments
 * @buffer: the buffer array
 * @flags:  the flags specifier
 * @width: the width given
 * @precision: the precision specification
 * @size: the size of specifier
 * Return: integer
 */
int print_rot13string(va_list arguments, char buffer[],
	int flags, int width, int precision, int size)
{
	char *string;
	char y;
	unsigned int j, k;
	int counter = 0;
	char i[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char o[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	string = va_arg(arguments, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (string == NULL)
		string = "(AHYY)";
	for (j = 0; string[j]; j++)
	{
		for (k = 0; i[k]; k++)
		{
			if (i[k] == string[j])
			{
				y = o[k];
				write(1, &y, 1);
				counter++;
				break;
			}
		}
		if (!i[k])
		{
			y = string[j];
			write(1, &y, 1);
			counter++;
		}
	}
	return (counter);
}


