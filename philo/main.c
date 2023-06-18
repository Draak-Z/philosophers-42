/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaudet <bmaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 18:21:05 by bmaudet           #+#    #+#             */
/*   Updated: 2021/10/28 21:24:33 by bmaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_death(t_data *data, int i, int *state)
{
	while (++i < data->arg.nb)
	{
		pthread_mutex_lock(&data->arg.time_eat);
		pthread_mutex_lock(&data->arg.finish);
		if ((get_time() - data->philo[i].last_meal) >= (long)(data->arg.d)
			&& !data->philo[i].finish)
		{
			pthread_mutex_unlock(&data->arg.finish);
			pthread_mutex_unlock(&data->arg.time_eat);
			pthread_mutex_lock(&data->arg.print);
			status("died\n", &data->philo[i]);
			pthread_mutex_unlock(&data->arg.print);
			life_status(&data->philo[i], 1);
			break ;
		}
		pthread_mutex_unlock(&data->arg.time_eat);
		pthread_mutex_unlock(&data->arg.finish);
	}
	pthread_mutex_lock(&data->arg.dead);
	if (data->arg.stop)
	{
		pthread_mutex_unlock(&data->arg.dead);
		*state = 1;
	}
}

void	end(t_data *data, int i, int *state)
{
	while (!*state)
	{
		check_death(data, -1, state);
		if (!*state)
			pthread_mutex_unlock(&data->arg.dead);
		ft_usleep(1);
	}
	while (++i < data->arg.nb)
		pthread_join(data->philo[i].tid, NULL);
	pthread_mutex_destroy(&data->arg.print);
	pthread_mutex_destroy(&data->arg.dead);
	pthread_mutex_destroy(&data->arg.time_eat);
	pthread_mutex_destroy(&data->arg.finish);
	i = -1;
	while (++i < data->arg.nb)
		pthread_mutex_destroy(&data->philo[i].l_fork);
	if (data->arg.stop == 2)
		printf("The philosophers ate %d time(s)\n", data->arg.nb_rep);
	free(data->philo);
}

int	init(t_data *data, int i)
{
	data->arg.start_time = get_time();
	data->arg.stop = 0;
	data->arg.philos_done = 0;
	pthread_mutex_init(&data->arg.print, NULL);
	pthread_mutex_init(&data->arg.dead, NULL);
	pthread_mutex_init(&data->arg.time_eat, NULL);
	pthread_mutex_init(&data->arg.finish, NULL);
	while (i < data->arg.nb)
	{
		data->philo[i].id = i + 1;
		data->philo[i].last_meal = data->arg.start_time;
		data->philo[i].nb_eat = 0;
		data->philo[i].finish = 0;
		data->philo[i].r_fork = NULL;
		pthread_mutex_init(&data->philo[i].l_fork, NULL);
		if (data->arg.nb == 1)
			return (1);
		if (i == data->arg.nb - 1)
			data->philo[i].r_fork = &data->philo[0].l_fork;
		else
			data->philo[i].r_fork = &data->philo[i + 1].l_fork;
		i++;
	}
	return (1);
}

int	parsing(int argc, char **argv, t_data *data, int i)
{
	int	j;

	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
			if (argv[i][j] < '0' || argv[i][j] > '9' || j > 10)
				return (0);
	}
	if ((argc == 5 || argc == 6))
	{
		data->arg.nb = ft_atoi(argv[1]);
		data->arg.d = ft_atoi(argv[2]);
		data->arg.e = ft_atoi(argv[3]);
		data->arg.s = ft_atoi(argv[4]);
		data->arg.nb_rep = -1;
		if (argc == 6)
			data->arg.nb_rep = ft_atoi(argv[5]);
		if (data->arg.nb <= 0 || data->arg.d <= 0 || data->arg.e <= 0 \
			|| data->arg.s <= 0 || data->arg.nb_rep == -2)
			return (0);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	i = -1;
	if (!(parsing(argc, argv, &data, 0)))
		return (ft_exit("Invalid Arguments\n"));
	if (!data.arg.nb_rep)
		return (ft_exit("The philosophers were not hungry\n"));
	data.philo = malloc(sizeof(t_philo) * data.arg.nb);
	if (!data.philo)
		return (ft_exit("Malloc failed\n"));
	init(&data, 0);
	while (++i < data.arg.nb)
	{
		data.philo[i].arg = &data.arg;
		if (pthread_create(&data.philo[i].tid, NULL, thread, &data.philo[i]))
		{
			free(data.philo);
			return (ft_exit("pthread_create returned an error\n"));
		}
	}
	i = 0;
	end(&data, -1, &i);
}
