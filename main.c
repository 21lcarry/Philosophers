#include "philosophers.h"

void	ft_kitchen(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	ft_print(gettime(philo->params.start), "take left fork", philo);
	pthread_mutex_lock(philo->right_fork);
	ft_print(gettime(philo->params.start), "take right fork", philo);
	ft_print(gettime(philo->params.start), "eating", philo);
	philo->last_eat = gettime(philo->params.start);
	ft_usleep(philo->params.t_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	ft_leisure(t_philo *philo)
{
	ft_print(gettime(philo->params.start), "sleeping", philo);
	ft_usleep(philo->params.t_sleep);
	ft_print(gettime(philo->params.start), "thinking", philo);
}

void	*ft_life(void *philos)
{
	t_philo	*philo;

	philo = (t_philo *)philos;
	while (1)
	{
		ft_kitchen(philo);
		++philo->count_eat;
		if ((philo->count_eat == philo->params.meal_count)
			&& philo->params.meal_count != -1)
			return (0);
		ft_leisure(philo);
	}
}

void	ft_process(t_main *main)
{
	int			i;
	pthread_t	tid;

	pthread_create(&tid, NULL, ft_monitor, main);
	i = -1;
	while (++i < main->params.count)
	{
		pthread_create(&main->philos->tid, NULL, ft_life, &main->philos[i]);
		usleep(50);
	}
	pthread_join(tid, NULL);
}

int	main(int ac, char **av)
{
	t_main	*main;

	if (ac < 5 || ac > 6 || !(ft_check_args(ac, av)))
		return (ft_exit("Invalid input\n", NULL));
	main = ft_init_main(av);
	if (main == NULL)
		return (ft_exit("Invalid input\n", NULL));
	else if (!ft_check_main(main, av))
		return (ft_exit("Invalid input\n", main));
	else
	{
		main->params.start = gettime(0);
		if (!ft_init_philo(main))
			return (ft_exit("Error: malloc error\n", main));
		ft_fork_of_hn(main);
		ft_process(main);
	}
	ft_free(main);
}
