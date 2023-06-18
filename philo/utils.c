/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaudet <bmaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 18:21:17 by bmaudet           #+#    #+#             */
/*   Updated: 2021/10/28 17:59:20 by bmaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int		i;
	long	sum;

	sum = 0;
	i = -1;
	while (str[++i])
		sum = (sum * 10) + (str[i] - 48);
	if (sum > 2147483647)
		return (-2);
	return (sum);
}

int	life_status(t_philo *philo, int i)
{
	pthread_mutex_lock(&philo->arg->dead);
	if (i)
		philo->arg->stop = i;
	if (philo->arg->stop)
	{
		pthread_mutex_unlock(&philo->arg->dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->arg->dead);
	return (0);
}

int	ft_exit(char *str)
{
	int	i;

	i = 0;
	write(2, "Error: ", 7);
	while (str[i])
		write(2, &str[i++], 1);
	return (0);
}

long int	get_time(void)
{
	long int			time;
	struct timeval		current_time;

	time = 0;
	if (gettimeofday(&current_time, NULL) == -1)
		ft_exit("Gettimeofday returned -1\n");
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time);
}

void	ft_usleep(long int time_in_ms)
{
	long int	start_time;

	start_time = 0;
	start_time = get_time();
	while ((get_time() - start_time) < time_in_ms)
		usleep(time_in_ms / 10);
}
