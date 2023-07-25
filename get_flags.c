#include "main.h"

/**
 * get_flags - func calculate flags
 * @format: Format string
 * @p: parameter
 * Return: flags
 */
int get_flags(const char *format, int *p)
{

	int index, current_p;
	int flags = 0;
	const char flags_chars[] = {'-', '+', '0', '#', ' ', '\0'};
	const int flags_array[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	for (current_p = *p + 1; format[current_p] != '\0'; current_p++)
	{
		for (index = 0; flags_chars[index] != '\0'; index++)
			if (format[current_p] == flags_chars[index])
			{
				flags |= flags_array[index];
				break;
			}

		if (flags_chars[index] == 0)
			break;
	}

	*p = current_p - 1;

	return (flags);
}

