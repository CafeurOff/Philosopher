/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_verifs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduthill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 17:13:34 by lduthill          #+#    #+#             */
/*   Updated: 2023/10/18 01:20:55 by lduthill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
**  Check if arguments are valid
*/

void	p_verif_args(t_data *data, int ac, char **av)
{
	if (ac < 5)
		ft_error(data, "Wrong number of arguments\n");
	if (ac > 6)
		ft_error(data, "Too number of arguments\n");
	p_args_is_int(data, ac, av);
}

/*
**  Check if arguments are integers
*/

void	p_args_is_int(t_data *data, int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				ft_error(data, "Arguments must be integers\n");
			j++;
		}
		i++;
	}
	p_args_to_int(data, ac, av);
}

/*
**  Convert arguments to int
*/

void	p_args_to_int(t_data *data, int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = ft_atoi(av[i]);
		if (j < 0)
			return (ft_error(data, "Arguments must be positive\n"));
		if (i == 1)
		{
			if (j == 0)
				return (ft_error(data, "Number of philosophers must be > 0\n"));
			data->nb_philo = j;
		}
		if (i == 2)
			data->time_to_die = j;
		if (i == 3)
			data->time_to_eat = j;
		if (i == 4)
			data->time_to_sleep = j;
		if (i++ == 5)
			data->nb_eat = j;
	}
}
