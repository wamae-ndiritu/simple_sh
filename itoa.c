#include <stdio.h>

/**
 * _itoa - converts integer into string
 * @n: integer to be converted
 * @str: pointer to the string converted
 * @base: base of conversion
 *
 * Return: Nothing.
 */

void _itoa(int n, char *str, int base)
{
	int i = 0;
	int start, end;
	int is_negative = 0;

	if (n < 0 && base == 10)
	{
		is_negative = 1;
		n = -n;
	}

	while (n != 0)
	{
		int rem = n % base;

		str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
		n = n / base;
	}

	if (is_negative)
	{
		str[i++] = '-';
	}

	str[i] = '\0';
	start = 0;
	end = i - 1;
	while (start < end)
	{
		char temp = str[start];

		str[start] = str[end];
		str[end] = temp;
		start++;
		end--;
	}
}

