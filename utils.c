#include "philosophers.h"

void	ft_free(t_main *main)
{
	int	i;

	if (main)
	{
		i = -1;
		if (main->forks != NULL)
			while (++i < main->params.count)
				pthread_mutex_destroy(&main->forks[i]);
		free(main->forks);
		free(main->philos);
		pthread_mutex_destroy(&main->write);
		free(main);
	}
}

void	*ft_monitor(void *main)
{
	int		last_full;
	int		i;
	t_main	*tmp;

	tmp = (t_main *)main;
	while (1)
	{
		last_full = 0;
		i = -1;
		while (++i < tmp->params.count)
		{
			if ((tmp->philos[i].count_eat >= tmp->params.meal_count)
				&& tmp->params.meal_count != -1)
				++last_full;
			if (!ft_death_check(main, i))
				return (0);
		}
		if (last_full == tmp->params.count)
			return (0);
	}
}

int	ft_atoi(const char *str)
{
	long int	tmp;
	long int	i;
	int			minus;

	tmp = 0;
	i = 0;
	minus = 1;
	while (str[i] == 32 || str[i] == '\t' || str[i] == '\n' || str[i] == '\r'
		|| str[i] == '\v' || str[i] == '\f')
		i++;
	if (str[i] == 43)
		minus = 1;
	if (str[i] == 45)
		minus = -1 + ((i++) * 0);
	while (str[i] != '\0' && (str[i] > 47 && str[i] < 58))
	{
		tmp = tmp * 10;
		tmp += str[i] - 48;
		i++;
		if (tmp > 2147483647 && minus != -1)
			return (-1);
		else if (tmp > 2147483648 && minus == -1)
			return (-1);
	}
	return (tmp * minus);
}

long	gettime(long start)
{
	struct timeval	tv;
	long			t;

	gettimeofday(&tv, NULL);
	t = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (t - start);
}

void	ft_usleep(int in)
{
	time_t	start;
	time_t	end;

	start = gettime(0);
	end = gettime(0) + in;
	while (start < end)
	{
		usleep (10);
		start = gettime(0);
	}
}
