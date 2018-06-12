/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 10:53:55 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/11 21:15:08 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "commandqueue.h"

static int32_t	comparetime(t_timeval *comtime);
static void		cleartime(t_timeval *comtime);
static void		settimer(t_timeval **time);
static void		setalarm(t_timeval *alarm, float factor);

t_server_methods server = {
	&comparetime,
	&cleartime,
	&settimer,
	&setalarm
};

static int32_t	comparetime(t_timeval *time)
{
	printf("\nCOMPARE TIME\nTimer set for <%ld> seconds & <%d> microseconds\nvs\n<%ld> seconds & <%d> microseconds\n", time->tv_sec, time->tv_usec, SRV_TIME.tv_sec, SRV_TIME.tv_usec);
	if ((SRV_TIME.tv_sec > time->tv_sec)
		|| (time->tv_sec == SRV_TIME.tv_sec && (SRV_TIME.tv_usec >=time->tv_usec)))
	{
		printf("Pull from commandqueue\n");
		return (1);
	}
	return (0);
}

static void		settimer(t_timeval **time)
{
	t_timeval	temp;
	t_timeval	*alarm;

	gettimeofday(&temp, NULL);
	printf("\nSET TIMER\nIt is <%ld> seconds & <%d> microseconds\n", temp.tv_sec, temp.tv_usec);
	if ((!(*time) && !(commandqueue.data)->first))
		;
	else
	{
		if ((commandqueue.data)->first)
		{
			if (!(*time))
				(*time) = (t_timeval *)calloc(1, sizeof(t_timeval));
			alarm = &(((t_command *)((commandqueue.data)->first->data))->alarm);
	printf("Alarm at <%ld> seconds & <%d> microseconds\n", alarm->tv_sec, alarm->tv_usec);
			(*time)->tv_sec = alarm->tv_sec - temp.tv_sec;
			if (alarm->tv_usec > temp.tv_usec)
				(*time)->tv_usec = alarm->tv_usec - temp.tv_usec;
			else
				(*time)->tv_usec = alarm->tv_usec;
			printf("Timer set for <%ld> seconds & <%d> microseconds\n", (*time)->tv_sec, (*time)->tv_usec);
		}
	}
}

static void		setalarm(t_timeval *alarm, float factor)
{
	t_timeval	temp;
	double		interval;
	int64_t		i_interval;
	double		integer;
	int64_t		i_integer;

	gettimeofday(&temp, NULL);
	printf("\nSET ALARM\nIt is <%ld> seconds & <%d> microseconds\n", temp.tv_sec, temp.tv_usec);
	interval = factor/SRV_GENV.timeinterval;
	integer = 0;
	if (interval > 1)
		interval = modf(interval, &integer);
	interval = (interval * 1000000);
	i_interval = (int64_t)interval;
	i_integer = (int64_t)integer;
	if (i_interval >= (1000000 - temp.tv_usec))
	{
		i_integer++;
		i_interval = i_interval - (1000000 - temp.tv_usec);
	}
	alarm->tv_sec = temp.tv_sec + i_integer;
	alarm->tv_usec = temp.tv_usec + i_interval;
	printf("Alarm at <%ld> seconds & <%d> microseconds\n", alarm->tv_sec, alarm->tv_usec);
}
