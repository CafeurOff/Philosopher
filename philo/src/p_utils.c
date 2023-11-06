/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduthill <lduthill@42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:42:02 by lduthill          #+#    #+#             */
/*   Updated: 2023/11/06 17:12:24 by lduthill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Free all my tables
** And destroy mutex if needed
*/

void	free_table(t_data *data)
{
	int	i;

	if (data->forks)
	{
		i = 0;
		while (i < data->nb_philo)
			pthread_mutex_destroy(&data->forks[i++]);
	}
	if (data->philo)
		free(data->philo);
	if (data->thread)
		free(data->thread);
	if (data->forks)
		free(data->forks);
	if (data->print)
		pthread_mutex_destroy(data->print);
}

/*
** Print error and free all my tables
*/

void	ft_error(t_data *data, char *str)
{
	free_table(data);
	printf("Error\n %s\n", str);
	exit(1);
}

/*
** Get time in milliseconds
*/

long long	get_time(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return (now.tv_sec * 1000 + now.tv_usec / 1000);
}

/*
**	Get time in milliseconds since the start of the program
*/

long long	get_time2(t_data *data)
{
	return (get_time() - data->start_time);
}

/*
**	Print Philosohper and lock print mutex
*/

void	print_p(t_data *data, const char *col, t_philo *philo, char *str)
{
	pthread_mutex_lock(&data->dead);
	if (philo->is_dead)
	{
		pthread_mutex_unlock(&data->dead);
		return ;
	}
	pthread_mutex_lock(data->print);
	if (!(philo->is_dead))
		printf("[%lld]	%s%d	%s%s\n", get_time2(data), col, \
		philo->id + 1, str, RESET);
	pthread_mutex_unlock(data->print);
	pthread_mutex_unlock(&data->dead);
}
