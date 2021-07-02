#include "philo.h"

int		ft_atoi(const char *string)
{
	unsigned long int	n;

	n = 0;
	while (*string == ' ' || *string == '\t' || *string == '\n'
		|| *string == '\v' || *string == '\f' || *string == '\r')
		string++;
	if (*string == '+')
	{
		string++;
	}
	while (*string >= '0' && *string <= '9')
	{
		if (n >= 9223372036854775807)
			return (-1);
		n = n * 10 + *(string++) - '0';
	}
	if (*string)
		return -1;
	return ((int)n);
}