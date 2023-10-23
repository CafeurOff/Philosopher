/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduthill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 22:20:13 by lduthill          #+#    #+#             */
/*   Updated: 2023/10/18 00:11:44 by lduthill         ###   ########.fr       */
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
	if (philo->is_dead)
		return (-1);
	pthread_mutex_lock(&data->forks[fork1]);
	if (philo->is_dead)
		return (-1);
	print_p(data, RED, philo, "has taken a fork\n");
	pthread_mutex_lock(&data->forks[fork2]);
	if (philo->is_dead)
		return (-1);
	philo->last_eat = get_time2(*data);
	eat_fork(data, philo);
	up_usleep(philo, data->time_to_eat);
	philo->nb_eat++;
	if (philo->is_dead)
		return (-1);
	pthread_mutex_unlock(&data->forks[fork1]);
	pthread_mutex_unlock(&data->forks[fork2]);
	if (philo->is_dead)
		return (-1);
	print_p(data, BLUE, philo, "is sleeping\n");
	up_usleep(philo, data->time_to_sleep);
	if (philo->is_dead)
		return (-1);
	print_p(data, GREEN, philo, "is thinking\n");
	return (0);
}

/*
**	Just print philo take a fork and eat norms :(
*/

void	eat_fork(t_data *data, t_philo *philo)
{
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
	while (i < data->nb_philo)
	{
		if (data->philo[i].nb_eat >= data->nb_eat)
			count++;
		i++;
	}
	return (count == data->nb_philo);
}

/*
**	Check if a philo is dead
*/

int	is_dead(t_data *data, int i)
{
	int	k;
	int	eat;
	int	time_die;

	eat = is_full(data);
	time_die = get_time2(*data) - data->philo[i].last_eat;
	if (eat || time_die > data->time_to_die)
	{
		k = 0;
		while (k < data->nb_philo)
			data->philo[k++].is_dead = 1;
		data->philo[i].culpable = 1;
		k = 0;
		while (k < data->nb_philo)
			pthread_mutex_unlock(&data->forks[k++]);
		if (!eat)
			print_p(data, PURPLE, &data->philo[i], "died\n");
		return (-1);
	}
	return (0);
}

/*
**	Here i have recoded usleep for get a large usleep
*/

void	up_usleep(t_philo *philo, long long time)
{
	long long	start;

	start = get_time();
	while (get_time() < start + time)
	{
		if (philo->is_dead)
			break ;
		usleep(500);
	}
}
