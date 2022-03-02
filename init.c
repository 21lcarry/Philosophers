#include "philosophers.h"

t_main	*ft_init_main(char **av)
{
	t_main	*main;

	main = (t_main *)malloc(sizeof(t_main));
	if (main == NULL)
		return (NULL);
	main->params.count = ft_atoi(av[1]);
	main->params.t_die = ft_atoi(av[2]);
	main->params.t_eat = ft_atoi(av[3]);
	main->params.t_sleep = ft_atoi(av[4]);
	if (av[5])
		main->params.meal_count = ft_atoi(av[5]);
	else
		main->params.meal_count = -1;
	return (main);
}

int	ft_init_forks(t_main *main)
{
	int	i;

	main->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* main->params.count);
	if (main->forks == NULL)
		return (0);
	i = -1;
	while (++i < main->params.count)
		pthread_mutex_init(&main->forks[i], NULL);
	return (1);
}

int	ft_init_philo(t_main *main)
{
	int	i;

	main->philos = (t_philo *)malloc(sizeof(t_philo) * main->params.count);
	if (main->philos == NULL)
		return (0);
	i = -1;
	while (++i < main->params.count)
	{
		main->philos[i].main = main;
		main->philos[i].params = main->params;
		main->philos[i].id = i + 1;
		main->philos[i].stop_flag = 0;
		main->philos[i].last_eat = 0;
		main->philos[i].count_eat = 0;
	}
	return (ft_init_forks(main));
}

int	ft_check_args(int ac, char **av)
{
	int	i;
	int	j;

	i = 0;
	while (++i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < 48 && av[i][j] > 57)
				return (0);
			else
				++j;
		}
	}
	return (1);
}

int	ft_check_main(t_main *main, char **av)
{
	if (main->params.count < 0 || main->params.t_die < 0
		|| main->params.t_eat < 0 || main->params.t_sleep < 0)
		return (0);
	if (av[5])
		if (main->params.meal_count < 0)
			return (0);
	return (1);
}
