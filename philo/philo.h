/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaudet <bmaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 18:21:27 by bmaudet           #+#    #+#             */
/*   Updated: 2021/10/28 21:22:08 by bmaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_arg
{
	int					nb;
	int					d;
	int					e;
	int					s;
	int					nb_rep;
	int					philos_done;
	int					stop;
	long int			start_time;
	pthread_mutex_t		print;
	pthread_mutex_t		dead;
	pthread_mutex_t		time_eat;
	pthread_mutex_t		finish;
}						t_arg;

typedef struct s_philo
{
	int					id;
	int					finish;
	long int			last_meal;
	unsigned int		nb_eat;
	pthread_t			tid;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		l_fork;
	t_arg				*arg;
}						t_philo;

typedef struct s_data
{
	t_philo				*philo;
	t_arg				arg;
}						t_data;

int						ft_exit(char *str);
int						life_status(t_philo *ph, int i);
int						ft_atoi(const char *str);
long int				get_time(void);
void					ft_usleep(long int time_in_ms);
void					*thread(void *data);
void					status(char *str, t_philo *philo);

#endif