#include "philo.h"
#include <stdio.h>
static int	ft_isdigit(int c)
{
	if ((c >= '0' && c <= '9') || c == ' ')
		return (1);
	else
		return (0);
}


static int	are_only_digit(char **argv)
{
	int	i;
	int	j;

	j = -1;
	while (argv[++j])
	{
		i = -1;
		while (argv[j][++i])
			if (!ft_isdigit(argv[j][i]))
				return (0);
	}
	return (1);
}


int	iserr_args(char **argv)
{
	int	j;
	int	nb;

	if (!are_only_digit(argv))
	{
		printf(RED"Seul les nombres sont acceptes\n"WHITE);
		return (1);
	}
	j = -1;
	while (argv[++j])
	{
		nb = ft_atoi(argv[j]);
		if ((j == 0 && (nb > 10000 || nb < 1)) || nb < 0)
		{
			if (j == 0)
				printf(RED"Nombre de philo invalide\n");
			else
				printf(RED"Argument invalide\n");
			return (1);
		}


	}
	return (0);
}
