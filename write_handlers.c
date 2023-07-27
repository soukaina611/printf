#include "main.h"

/*************************function handle_write_char *************************/
/**
 * handle_write_char - function that Print a string
 * @character: the character
 * @buffer: the buffer array
 * @flags:  the flags of specifier
 * @width: the width
 * @precision: the precision specified
 * @size: the size of specifier
 * Return: the value of char
 */
int handle_write_char(char character, char buffer[],
	int flags, int width, int precision, int size)
{
	char p_add = ' ';
	int l = 0;

	UNUSED(size);
	UNUSED(precision);

	if (flags & F_ZERO)
		p_add = '0';

	buffer[l++] = c;
	buffer[l] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (l = 0; l < width - 1; l++)
			buffer[BUFF_SIZE - l - 2] = p_add;

		if (flags & F_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - l - 1], width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - l - 1], width - 1) +
					write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}

/************************function write_number *************************/
/**
 * write_number - a function that write a number
 * @is_num_negative: if number is negative < 0
 * @index: the index of number to add to buffer
 * @buffer: the buffer array
 * @flags:  the flags of specifier
 * @width: the width given
 * @precision: the precision speci
 * @size: the size of specifier
 * Return: the number
 */
int write_number(int is_num_negative, int index, char buffer[],
	int flags, int width, int precision, int size)
{
	char ex_char = 0, padding = ' ';

	UNUSED(size);

	int len = BUFF_SIZE - index - 1;

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padding = '0';
	if (is_num_negative)
		ex_char = '-';
	else if (flags & F_PLUS)
		ex_char = '+';
	else if (flags & F_SPACE)
		ex_char = ' ';

	return (write_num(index, buffer, flags, width, precision,
		len, padding, ex_char));
}
/**
 * write_num - function that write number
 * @i:  the index where the number begins on the buffer
 * @buffer:  the buffer array
 * @flags: the flags specifier
 * @width: the width given
 * @precision: the precision of specifier
 * @len: the length
 * @padding: the pad character
 * @ex_char: the extra character
 * Return: the number printed
 */
int write_num(int i, char buffer[],
	int flags, int width, int precision,
	int len, char padding, char ex_char)
{
	int j, padding_st = 1;

	if (precision == 0 && i == BUFF_SIZE - 2 && buffer[i] == '0' && width == 0)
		return (0);
	if (precision == 0 && i == BUFF_SIZE - 2 && buffer[i] == '0')
		buffer[i] = padding = ' ';
	if (precision > 0 && precision < len)
		padding = ' ';
	while (precision > len)
		buffer[--i] = '0', len++;
	if (ex_char != 0)
		len++;
	if (width > len)
	{
		for (j = 1; j < width - len + 1; j++)
			buffer[j] = padding;
		buffer[j] = '\0';
		if (flags & F_MINUS && padding == ' ')
		{
			if (ex_char)
				buffer[--i] = ex_char;
			return (write(1, &buffer[i], len) + write(1, &buffer[1], j - 1));
		}
		else if (!(flags & F_MINUS) && padding == ' ')
		{
			if (ex_char)
				buffer[--i] = ex_char;
			return (write(1, &buffer[1], j - 1) + write(1, &buffer[i], len));
		}
		else if (!(flags & F_MINUS) && padding == '0')
		{
			if (ex_char)
				buffer[--padding_st] = ex_char;
			return (write(1, &buffer[padding_st], j - padding_st) +
				write(1, &buffer[i], len - (1 - padding_st)));
		}
	}
	if (ex_char)
		buffer[--i] = ex_char;
	return (write(1, &buffer[i], len));
}

/**
 * write_unsgnd - function that write unsigned num
 * @is_num_negative: indicate if the number is negative
 * @index: the index at which the number begin in the buffer
 * @buffer: the array of characters
 * @flags: the flags of specifier
 * @width: the width specifier
 * @precision: the precesion specifier
 * @size: the size specifier
 * Return: unsigned number
 */
int write_unsgnd(int is_num_negative, int index,
	char buffer[], int flags, int width, int precision, int size)
{

	char padding = ' ';
	int len = BUFF_SIZE - index - 1, k = 0;

	UNUSED(size);
	UNUSED(is_num_negative);

	if (precision == 0 && index == BUFF_SIZE - 2 && buffer[index] == '0')
		return (0);
	if (precision > 0 && precision < len)
		padding = ' ';

	while (precision > len)
	{
		buffer[--index] = '0';
		len++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padding = '0';

	if (width > len)
	{
		for (k = 0; k < width - len; k++)
			buffer[k] = padding;

		buffer[k] = '\0';

		if (flags & F_MINUS)
		{
			return (write(1, &buffer[index], len) + write(1, &buffer[0], k));
		}
		else
		{
			return (write(1, &buffer[0], k) + write(1, &buffer[index], len));
		}
	}

	return (write(1, &buffer[index], len));
}

/**
 * write_pointer - function that write memory address of pointer
 * @buffer: the array of characters
 * @index: the index at which the number begin in the buffer
 * @len: the length
 * @width: the width given
 * @flags: the flags of specifier
 * @padding: the character that represent padding
 * @ex_char: the extra character
 * @padding_st: the index where padding should begin
 * Return: Number of written pointer
 */
int write_pointer(char buffer[], int index, int len,
	int width, int flags, char padding, char ex_char, int padding_st)
{
	int k;

	if (width > len)
	{
		for (k = 3; i < width - len + 3; k++)
			buffer[k] = padding;
		buffer[k] = '\0';
		if (flags & F_MINUS && padding == ' ')
		{
			buffer[--index] = 'x';
			buffer[--index] = '0';
			if (ex_char)
				buffer[--index] = ex_char;
			return (write(1, &buffer[index], len) + write(1, &buffer[3], k - 3));
		}
		else if (!(flags & F_MINUS) && padding == ' ')
		{
			buffer[--index] = 'x';
			buffer[--index] = '0';
			if (ex_char)
				buffer[--index] = ex_char;
			return (write(1, &buffer[3], k - 3) + write(1, &buffer[index], len));
		}
		else if (!(flags & F_MINUS) && padding == '0')
		{
			if (ex_char)
				buffer[--padding_st] = ex_char;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[padding_st], k - padding_st) +
				write(1, &buffer[index], len - (1 - padding_st) - 2));
		}
	}
	buffer[--index] = 'x';
	buffer[--index] = '0';
	if (ex_char)
		buffer[--index] = ex_char;
	return (write(1, &buffer[index], BUFF_SIZE - index - 1));
}

