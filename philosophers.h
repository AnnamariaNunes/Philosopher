/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annamarianunes <annamarianunes@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 19:35:33 by annamarianu       #+#    #+#             */
/*   Updated: 2024/05/18 19:35:36 by annamarianu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h> 
# include <stdio.h> 
# include <stdlib.h> 
# include <pthread.h> 
# include <sys/time.h> 

// simulation status
# define STOP 0

// fork available
# define NO 0
# define YES 1

// handle input
# define OK 0
# define FAILED 1
# define VALID 1
# define NOT_VALID 0
# define E_INVAL 22
# define INT_MAX 2147483647

# define RED "\033[38;2;222;56;43m"
# define BLUE "\033[38;2;34;183;235m"
# define RESET "\033[0m"

typedef struct s_time
{
	int	to_die;
	int	eating;
	int	sleeping;
}				t_time;

typedef struct s_fork
{
	int				available;
	pthread_mutex_t	lock;
}					t_fork;

typedef struct s_data
{
	int				nbr_of_philos;
	int				nbr_of_times_must_eat;
	int				simulation;
	int				**order;
	t_time			time;
	long long		starting_time;
	pthread_mutex_t	lock_print;
	pthread_mutex_t	lock_data;
}					t_data;

typedef struct s_args
{
	int				nbr;
	int				must_eat;
	int				iteration;
	t_data			*data;
	t_fork			*left_fork;
	t_fork			*right_fork;
	long long		last_eat;
	long long		next_eat;
	pthread_mutex_t	lock_philo;
}				t_args;

// input
int			handle_input(int argc, char *argv[], t_data *input);
void		fill_data(t_data *data);

// threads
t_fork		*create_forks(int nbr_of_forks);
t_args		*create_args(t_data *data, t_fork *forks);
pthread_t	*create_philos(int nbr_of_philos, t_args *args);
void		*only_one_philo_routine(void *philo_args);
void		*routine(void *arg);
void		join_philos(pthread_t *philos, int nbr_of_philos);

// philosopher's actions
void		philo_eats(int philo, int time_eating, t_args *args);
void		philo_takes_forks(int nbr, long long starting_time, t_args *philo);
void		philo_drops_forks(t_args *philo);
void		philo_sleeps(int philo, int time_to_spleep, long long starting_time,
				t_data *data);
void		philo_thinks(int philo, long long starting_time, t_data *data);

// monitoring simulation
int			simulation(t_data *data);
void		set_simulation(t_data *data);
void		simulation_monitoring(t_args *philos, t_data *data);

// time
long long	time_now(void);
long long	get_delta_time(long long start);
void		time_wait(int delta_time, long long start);
void		time_wait2(int time_to_wait, long long start);

// utils
int			ft_isdigit(int c);
int			ft_atoi(const char *nptr);
long int	ft_atol(const char *nptr);
void		*malloc_error(void);
void		print_action(long long time, int philo, char *action, t_data *data);
void		clean_variables(t_data *data, t_fork *forks, t_args *args,
				pthread_t *philos);
int			handle_error(int error, t_data *data, t_fork *forks, t_args *args);
int			has_fork(t_fork *fork);

#endif
