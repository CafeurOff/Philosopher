/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduthill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 00:06:44 by lduthill          #+#    #+#             */
/*   Updated: 2023/10/18 00:48:45 by lduthill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
**  Init philo struct to -1 or NULL values
*/

void	p_init(t_data *data)
{
	data->nb_philo = -1;
	data->time_to_die = -1;
	data->time_to_eat = -1;
	data->time_to_sleep = -1;
	data->nb_eat = -1;
	data->forks = NULL;
	data->philo = NULL;
	data->thread = NULL;
	data->print = NULL;
	data->start_time = get_time();
}

/*
**  Init philo struct
**  Malloc philo struct
*/

void	p_init_p(t_data *data)
{
	t_philo		*philo;
	int			i;

	philo = malloc(sizeof(t_philo) * data->nb_philo);
	i = 0;
	if (!philo)
		ft_error(data, "Malloc failed\n");
	while (i < data->nb_philo)
	{
		p_init_philo(data, &philo[i], i);
		i++;
	}
	data->philo = philo;
	init_forks(data);
	init_threads(data);
}

/*
**  Init philo struct
**  Set philo struct values
*/

void	p_init_philo(t_data *data, t_philo *philo, int id)
{
	philo->id = id;
	philo->forks = 0;
	philo->is_dead = 0;
	philo->nb_eat = 0;
	philo->last_eat = 0;
	philo->culpable = 0;
	philo->data = data;
}

/*
** Init forks with mutex
*/

void	init_forks(t_data *data)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	i = 0;
	if (!forks)
		ft_error(data, "Malloc failed\n");
	while (i < data->nb_philo)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	data->forks = forks;
}

/*
** Init threads
*/
void	init_threads(t_data *data)
{
	pthread_t	*thread;

	thread = malloc(sizeof(pthread_t) * data->nb_philo);
	if (!thread)
		ft_error(data, "Malloc failed\n");
	data->thread = thread;
}
