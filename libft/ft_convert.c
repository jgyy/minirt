#include "libft.h"

int	ft_atoi(const char *str)
{
	long	res;
	int		sign;

	res = 0;
	sign = 1;
	while (ft_isspace((unsigned char)*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit((unsigned char)*str))
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	return ((int)(res * sign));
}

double	ft_atof(const char *str)
{
	double	res;
	double	sign;
	double	frac;

	res = 0;
	sign = 1.0;
	frac = 0.1;
	while (ft_isspace((unsigned char)*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1.0;
		str++;
	}
	while (ft_isdigit((unsigned char)*str))
		res = res * 10.0 + (*str++ - '0');
	if (*str == '.')
	{
		str++;
		while (ft_isdigit((unsigned char)*str))
		{
			res += (*str++ - '0') * frac;
			frac *= 0.1;
		}
	}
	return (res * sign);
}
