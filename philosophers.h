#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <time.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_params
{
	int		count;
	int		t_die;
	long	t_eat;
	int		t_sleep;
	int		meal_count;
	long	start;
}	t_params;

typedef struct s_philo
{
	pthread_t		tid;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_main	*main;
	t_params		params;
	int				id;
	int				stop_flag;
	long			last_eat;
	int				count_eat;
}	t_philo;

typedef struct s_main
{
	t_philo			*philos;
	t_params		params;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
}	t_main;

void	ft_process(t_main *main);
void	*ft_life(void *philos);
void	ft_leisure(t_philo *philo);
void	ft_kitchen(t_philo *philo);

int		ft_check_main(t_main *main, char **av);
int		ft_check_args(int ac, char **av);
int		ft_init_philo(t_main *main);
int		ft_init_forks(t_main *main);
t_main	*ft_init_main(char **av);

void	ft_usleep(int in);
long	gettime(long start);
int		ft_atoi(const char *str);
void	*ft_monitor(void *main);
void	ft_free(t_main *main);
int		ft_exit(char *str, t_main *main);
void	ft_print(long start, char *msg, t_philo *philo);
int		ft_death_check(t_main *main, int i);
void	ft_fork_of_hn(t_main *main);

#endif