/* ************************************************************************** */
/*                                                                          */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduthill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 22:20:13 by lduthill          #+#    #+#             */
/*   Updated: 2023/11/06 14:44:31 by lduthill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
**	Here is philo routine
**	All check philo->is_dead to know if a philo is dead or not after each action
**	First, philo take 2 forks
**	Then, philo eat
**	Then, philo sleep
*/

int	p_loop(t_data *data, t_philo *philo, int fork1, int fork2)
{
	if (philo_is_dead(philo, 0, 0, 0))
		return (-1);
	pthread_mutex_lock(&data->forks[fork1]);
	if (philo_is_dead(philo, 1, fork1, 0))
		return (-1);
	print_p(data, RED, philo, "has taken a fork\n");
	pthread_mutex_lock(&data->forks[fork2]);
	if (philo_is_dead(philo, 2, fork1, fork2))
		return (-1);
	last_eat(data, philo);
	eat_fork(data, philo);
	up_usleep(philo, data->time_to_eat);
	eating(data, philo);
	if (philo_is_dead(philo, 2, fork1, fork2))
		return (-1);
	pthread_mutex_unlock(&data->forks[fork1]);
	pthread_mutex_unlock(&data->forks[fork2]);
	if (philo_is_dead(philo, 0, 0, 0))
		return (-1);
	print_p(data, BLUE, philo, "is sleeping\n");
	up_usleep(philo, data->time_to_sleep);
	if (philo_is_dead(philo, 0, 0, 0))
		return (-1);
	print_p(data, GREEN, philo, "is thinking\n");
	return (0);
}

int	philo_is_dead(t_philo *philo, int i, int fork1, int fork2)
{
	pthread_mutex_lock(&philo->data->dead);
	if (philo->is_dead)
	{
		if (i >= 1)
			pthread_mutex_unlock(&philo->data->forks[fork1]);
		if (i == 2)
			pthread_mutex_unlock(&philo->data->forks[fork2]);
		pthread_mutex_unlock(&philo->data->dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->dead);
	return (0);
}

/*
**	Just print philo take a fork and eat norms :(
*/

void	eat_fork(t_data *data, t_philo *philo)
{
	if (philo->nb_eat == data->nb_eat)
		return ;
	print_p(data, RED, philo, "has taken a fork\n");
	print_p(data, YELLOW, philo, "is eating\n");
}

/*
**	Check if a philo are eating enought
*/

int	is_full(t_data *data)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (data->nb_eat < 0)
		return (0);
	pthread_mutex_lock(&data->eating);
	while (i < data->nb_philo)
	{
		if (data->philo[i].nb_eat >= data->nb_eat)
			count++;
		i++;
	}
	pthread_mutex_unlock(&data->eating);
	return (count == data->nb_philo);
}

/*
**	Check if a philo is dead
*/

int	is_dead(t_data *data, int i)
{
	int	j;
	int	eat;
	int	time_die;

	eat = is_full(data);
	pthread_mutex_lock(&data->eat);
	time_die = get_time2(data) - data->philo[i].last_eat;
	pthread_mutex_unlock(&data->eat);
	if (eat || time_die > data->time_to_die)
	{
		j = 0;
		if (eat <= 0)
			print_p(data, PURPLE, &data->philo[i], "died\n");
		pthread_mutex_lock(&data->dead);
		while (j < data->nb_philo)
			data->philo[j++].is_dead = 1;
		pthread_mutex_unlock(&data->dead);
		return (-1);
	}
	return (0);
}
