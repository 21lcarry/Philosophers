#include "philosophers.h"

int	ft_exit(char *str, t_main *main)
{
	if (main)
	{
		if (main->philos)
			free(main->philos);
		free(main);
	}
	printf("%s", str);
	return (1);
}

void	ft_print(long start, char *msg, t_philo *philo)
{
	pthread_mutex_lock(&philo->main->write);
	printf("%ld philosopher %d %s\n", start, philo->id, msg);
	if (!philo->stop_flag)
		pthread_mutex_unlock(&philo->main->write);
}

int	ft_death_check(t_main *main, int i)
{
	if (gettime(main->params.start) - main->philos[i].last_eat
		> (main->params.t_die))
	{
		main->philos[i].stop_flag = 1;
		ft_print(gettime(main->params.start), "die", &main->philos[i]);
		return (0);
	}
	return (1);
}

void	ft_fork_of_hn(t_main *main)
{
	int	i;

	i = -1;
	while (++i < main->params.count - 1)
	{
		main->philos[i].left_fork = &main->forks[i];
		main->philos[i].right_fork = &main->forks[i + 1];
	}
	main->philos[i].left_fork = &main->forks[i];
	main->philos[i].right_fork = &main->forks[0];
}
