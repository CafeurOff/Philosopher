/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduthill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:24:45 by lduthill          #+#    #+#             */
/*   Updated: 2023/10/18 00:43:38 by lduthill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Routine for death
** Check if a philo is dead
** If a philo is dead, set is_dead to 1 and culpable to the philo who killed him
*/

void	*death_routine(void *args)
{
	t_data	*data;
	int		i;

	data = (t_data *)args;
	while (1)
	{
		i = 0;
		while (i < data->nb_philo)
		{
			if (is_dead(data, i) == -1)
				break ;
			i++;
		}
	}
	pthread_exit(NULL);
	return (NULL);
}

/*
** Routine for philo
** Change activity to eat, sleep and think
*/

void	*philo_routine(void *args)
{
	t_philo	*philo;
	t_data	*data;
	int		i;
	int		fork1;
	int		fork2;

	philo = (t_philo *)args;
	data = (t_data *)philo->data;
	fork1 = philo->id;
	fork2 = fork1 + 1;
	if (fork2 >= data->nb_philo)
		fork2 = 0;
	i = 0;
	while (1)
	{
		if (p_loop(data, philo, fork1, fork2) == -1)
			break ;
		i++;
	}
	return (NULL);
}

/*
** Init print mutex
*/

void	init_pm(t_data *data, pthread_mutex_t *print)
{
	pthread_mutex_init(print, NULL);
	data->print = print;
}

/*
** Main
** Verif arguments if they are valid and set base variables to data struct
** Init philo struct and mutex
** Create threads
** Join threads
** Free struct philo
*/

int	main(int ac, char **av)
{
	pthread_t			die;
	pthread_mutex_t		print;
	t_data				data;
	int					i;

	i = 0;
	p_init(&data);
	p_verif_args(&data, ac, av);
	p_init_p(&data);
	init_pm(&data, &print);
	pthread_create(&die, NULL, &death_routine, (void *)&data);
	while (i < data.nb_philo)
	{
		pthread_create(&data.thread[i], NULL, &philo_routine, \
		(void *)&data.philo[i]);
		up_usleep(&data.philo[i], !(i % 2));
		i++;
	}
	pthread_detach(die);
	i = 0;
	while (i < data.nb_philo)
		pthread_join(data.thread[i++], NULL);
	free_table(&data);
	return (0);
}
