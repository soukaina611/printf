#include "main.h"
/**
 * is_printable - function that evaluate if a character is printable
 * @character: the character to evaluate
 * Return: 1 if is printable else 0
 */
int is_printable(char character)
{
	if (character >= 32 && character < 127)
		return (1);

	return (0);
}
/**
 * append_hexa_code -  function that add ASCII CODE in hexadecimal  to buffer
 * @buffer: the array of characters
 * @index: the index to begin adding
 * @ascii: the ascii code
 * Return: 3
 */
int append_hexa_code(char ascii, char buffer[], int index)
{
	char map[] = "0123456789ABCDEF";
	/* The hexa format code is always 2 digits long */
	if (ascii < 0)
		ascii *= -1;

	buffer[index++] = '\\';
	buffer[index++] = 'x';

	buffer[index++] = map[ascii / 16];
	buffer[index] = map[ascii % 16];
	return (3);
}

/**
 * is_digit - function that verify if a character is a digit number
 * @character: the char to evaluate
 * Return: 1 if digit else 0
 */
int is_digit(char character)
{
	if (character >= '0' && character <= '9')
		return (1);

	return (0);
}

/**
 * convert_size_number - function that cast a number to specified type size
 * @number: the number to cast
 * @size_type: the type of number to cast
 * Return: the casted value of the number
 */
long int convert_size_number(long int number, int size_type)
{
	if (size_type == S_LONG)
		return (number);
	else if (size_type == S_SHORT)
		return ((short)number);

	return ((int)number);
}
/**
 * convert_size_unsgnd - function that cast a number to specified type
 * @number: the number to cast
 * @size_type: the type of number to cast
 * Return: the casted value of the number
 */
long int convert_size_unsgnd(unsigned long int number, int size_type)
{
	if (size_type == S_LONG)
		return (number);
	else if (size_type == S_SHORT)
		return ((unsigned short)number);

	return ((unsigned int)number);
}

