#include "main.h"

/***********************Function print_char *************************/
/**
 * print_char - function that prints a character
 * @arguments: the list a of arguments
 * @buffer: the buffer array
 * @flags:  the flags specifier
 * @width: the width specification
 * @precision: the precision specification
 * @size: the size of specifier
 * Return: the number of characters printed
 */
int print_char(va_list arguments, char buffer[],
	int flags, int width, int precision, int size)
{
	char c = va_arg(arguments, int);

	return (handle_write_char(c, buffer, flags, width, precision, size));
}
/************************* function print_string *************************/
/**
 * print_string - function that prints a string
 * @arguments: List a of arguments
 * @buffer: the buffer array
 * @flags:  the flags specifier
 * @width: the width
 * @precision: Precision specification
 * @size:  the size of specifier
 * Return:the string printed
 */
int print_string(va_list arguments, char buffer[],
	int flags, int width, int precision, int size)
{
	int len = 0, index;
	char *string = va_arg(arguments, char *);

	UNUSED(buffer);
	UNUSED(width);
	UNUSED(flags);
	UNUSED(precision);
	UNUSED(size);
	if (string == NULL)
	{
		string = "(null)";
		if (precision >= 6)
			string = "      ";
	}

	while (string[len] != '\0')
		len++;

	if (precision >= 0 && precision < len)
		len = precision;

	if (width > len)
	{
		if (flags & F_MINUS)
		{
			write(1, &string[0], len);
			for (index = width - len; index > 0; index--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (index = width - len; index > 0; index--)
				write(1, " ", 1);
			write(1, &string[0], len);
			return (width);
		}
	}

	return (write(1, string, len));
}
/************************* function print_percent *************************/
/**
 * print_percent -  function that print a percent sign
 * @arguments:  the lists of arguments
 * @buffer: the buffer array
 * @flags:  the flags specifier
 * @width: the width given
 * @precision: Precision specification
 * @size: the size of specifier
 * Return: percent sign
 */
int print_percent(va_list arguments, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(arguments);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/*************************function print_int *************************/
/**
 * print_int - function print an integer
 * @arguments: the list of arguments
 * @buffer: the Buffer array
 * @flags:  the flags specifier
 * @width: the width given
 * @precision: the precision specification
 * @size: the size specifier
 * Return: an integer
 */
int print_int(va_list arguments, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned long int x;
	int j = BUFF_SIZE - 2;
	int is_negative = 0;
	long int arg = va_arg(arguments, long int);

	arg = convert_size_number(arg, size);

	if (arg == 0)
		buffer[j--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	x = (unsigned long int)arg;

	if (arg < 0)
	{
		x = (unsigned long int)((-1) * arg);
		is_negative = 1;
	}

	while (x > 0)
	{
		buffer[j--] = (x % 10) + '0';
		x /= 10;
	}

	j++;

	return (write_number(is_negative, j, buffer, flags, width, precision, size));
}

/***********************function print_binary ************************/
/**
 * print_binary - function prints unsigned number
 * @arguments: the list of arguments
 * @buffer: the buffer array
 * @flags:  flags specifier
 * @width:  the width given
 * @precision: the precision specification
 * @size: the size of specifier
 * Return: the binary number.
 */
int print_binary(va_list arguments, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int index, a, b, somme;
	int counter;
	unsigned int c[32];

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	a = va_arg(arguments, unsigned int);
	b = 2147483648;
	c[0] = a / b;
	for (index = 1; index < 32; index++)
	{
		b /= 2;
		c[index] = (a / b) % 2;
	}
	for (index = 0, somme = 0, counter = 0; index < 32; index++)
	{
		somme += c[index];
		if (somme || index == 31)
		{
			char e = '0' + c[index];

			write(1, &e, 1);
			counter++;
		}
	}
	return (counter);
}

