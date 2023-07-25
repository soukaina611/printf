#include "main.h"

/**********************function print_unsigned number**********************/
/**
 * print_unsigned -  function that prints unsigned number
 * @arguments: the list of arguments
 * @buffer: the buffer array
 * @flags:  the flags specifier
 * @width: the given width
 * @precision: the precision specification
 * @size: the size of specifier
 * Return: integer
 */
int print_unsigned(va_list arguments, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned long int arg = va_arg(arguments, unsigned long int);
	int j = BUFF_SIZE - 2;

	arg = convert_size_unsgnd(arg, size);

	if (arg == 0)
		buffer[j--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (arg > 0)
	{
		buffer[j--] = (arg % 10) + '0';
		arg /= 10;
	}

	j++;

	return (write_unsgnd(0, j, buffer, flags, width, precision, size));
}

/*************function print_octal number****************/
/**
 * print_octal - function print unsigned number in octal
 * @arguments: the list of arguments
 * @buffer: the buffer array
 * @flags:  the flags specifier
 * @width: width
 * @precision: the precision specification
 * @size: the size of specifier
 * Return: the number in octal notation
 */
int print_octal(va_list arguments, char buffer[],
	int flags, int width, int precision, int size)
{

	int j = BUFF_SIZE - 2;
	unsigned long int arg = va_arg(arguments, unsigned long int);
	unsigned long int init_arg = arg;

	UNUSED(width);

	arg = convert_size_unsgnd(arg, size);

	if (arg == 0)
		buffer[j--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (arg > 0)
	{
		buffer[j--] = (arg % 8) + '0';
		arg /= 8;
	}

	if (flags & F_HASH && init_arg != 0)
		buffer[j--] = '0';

	j++;

	return (write_unsgnd(0, j, buffer, flags, width, precision, size));
}

/**************function print_hexadecimal **************/
/**
 * print_hexadecimal -  function that print unsigned number in hexadecimal
 * @arguments: the list of arguments
 * @buffer: the buffer array
 * @flags:  the flags specifier
 * @width: the width
 * @precision: the precision specification
 * @size: the size specifier
 * Return: the number in hexa
 */
int print_hexadecimal(va_list arguments, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(arguments, "0123456789abcdef", buffer,
		flags, 'x', width, precision, size));
}

/*************function_hexa_upper *********************/
/**
 * print_hexa_upper - function print unsigned number in upper hexadecimal
 * @arguments: the list of arguments
 * @buffer: the buffer array
 * @flags:  the flags specifier
 * @width: the width given
 * @precision: the precision specification
 * @size: the size specifier
 * Return: the number in upper hexa
 */
int print_hexa_upper(va_list arguments, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(arguments, "0123456789ABCDEF", buffer,
		flags, 'X', width, precision, size));
}

/**************function print_ hexa***********************/
/**
 * print_hexa - function that print hexadecimal number in upper or lower
 * @arguments: the list of arguments
 * @mapping_to:  the array of values that can be used to map the number to
 * @buffer: the buffer array
 * @flags:  the flags specifier
 * @flag_char: the flags character
 * @width: the width
 * @precision: the precision specification given
 * @size:  the size specifier
 * Return: Number of chars printed
 */
int print_hexa(va_list arguments, char mapping_to[], char buffer[],
	int flags, char flag_char, int width, int precision, int size)
{
	int j = BUFF_SIZE - 2;
	unsigned long int arg = va_arg(arguments, unsigned long int);
	unsigned long int init_arg = arg;

	UNUSED(width);

	arg = convert_size_unsgnd(arg, size);

	if (arg == 0)
		buffer[j--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (arg > 0)
	{
		buffer[j--] = mapping_to[arg % 16];
		arg /= 16;
	}

	if (flags & F_HASH && init_arg != 0)
	{
		buffer[j--] = flag_char;
		buffer[j--] = '0';
	}

	j++;

	return (write_unsgnd(0, j, buffer, flags, width, precision, size));
}

