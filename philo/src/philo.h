/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduthill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:24:58 by lduthill          #+#    #+#             */
/*   Updated: 2023/10/19 14:22:02 by lduthill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <string.h>
# include "../inc/libft/libft.h"

# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define CYAN "\033[0;36m"
# define RESET "\033[0m"

typedef struct s_philo
{
	int					id;
	int					forks;
	int					is_dead;
	int					culpable;
	int					nb_eat;
	long long			last_eat;
	struct s_data		*data;
}		t_philo;

typedef struct s_data
{
	int					nb_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nb_eat;
	long long			start_time;
	pthread_t			*thread;
	t_philo				*philo;
	pthread_mutex_t		*forks;
	pthread_mutex_t		*print;
}		t_data;

/* Main */
void		*death_routine(void *args);
void		*philo_routine(void *args);
void		init_pm(t_data *data, pthread_mutex_t *print);

/* Init*/
void		p_init(t_data *philo);
void		p_init_p(t_data *data);
void		p_init_philo(t_data *data, t_philo *philo, int id);
void		init_forks(t_data *data);
void		init_threads(t_data *data);
/* Utils */
void		free_table(t_data *data);
void		ft_error(t_data *data, char *str);
void		print_p(t_data *data, const char *col, t_philo *philo, char *str);
long long	get_time(void);
long long	get_time2(t_data data);
/* Verifs */
void		p_verif_args(t_data *philo, int ac, char **av);
void		p_args_is_int(t_data *philo, int ac, char **av);
void		p_args_to_int(t_data *philo, int ac, char **av);
/* Philo */
int			p_loop(t_data *data, t_philo *philo, int fork1, int fork2);
void		eat_fork(t_data *data, t_philo *philo);
int			is_full(t_data *data);
int			is_dead(t_data *data, int i, int *die);
void		up_usleep(t_philo *philo, long long time);

#endif
