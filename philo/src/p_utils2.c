/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduthill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:09:02 by lduthill          #+#    #+#             */
/*   Updated: 2023/11/06 22:25:31 by lduthill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	last_eat(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->eat);
	philo->last_eat = get_time() - data->start_time;
	pthread_mutex_unlock(&data->eat);
}

void	eating(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->eating);
	philo->nb_eat++;
	pthread_mutex_unlock(&data->eating);
}

int	ft_atoi(char *str)
{
	int	sign;
	int	i;
	int	res;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] == 32 || str[i] == 9)
		i++;
	if (str[0] == '-' || str[0] == '+')
	{
		if (str[0] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		res = res * 10 + str[i++] - 48;
	return (sign * res);
}
