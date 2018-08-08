/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 10:53:55 by nkouris           #+#    #+#             */
/*   Updated: 2018/08/07 16:39:46 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "time.h"
#include "events.h"

static int32_t	compare(t_timeval *relative, t_timeval *time2);
static void		setalarm(t_timeval *alarm, double factor);
static void		settimer(t_timeval **timer);

__attribute__((constructor))void	construct_time(void)
{
	time.compare = &compare;
	time.setalarm = &setalarm;
	time.settimer = &settimer;
}

static t_timeval	*_nearestalarm(void)
{
	if (!(event.queue.data->first))
		return (NULL);
	return (&(((t_event *)(event.queue.data->first->data))->alarm));
}

static void		settimer(t_timeval **timer)
{
	t_timeval	temp;
	t_timeval	*alarm;

	gettimeofday(&temp, NULL);
	if (!(alarm = _nearestalarm()))
	{
		if (*timer)
			ft_memdel((void **)timer);
		//printf("  No events to check\n");
		return ;
	}
	if (!(*timer))
		(*timer) = (t_timeval *)calloc(1, sizeof(t_timeval));
	printf("  Alarm pulled : <%ld> seconds & <%d> microseconds\n",
		alarm->tv_sec, alarm->tv_usec);
	(*timer)->tv_sec = alarm->tv_sec - temp.tv_sec;
	if ((*timer)->tv_sec < 0
		|| ((((*timer)->tv_usec = alarm->tv_usec - temp.tv_usec) < 0)
		&& !(*timer)->tv_sec))
		bzero((*timer), sizeof(t_timeval));
	else if ((*timer)->tv_usec < 0)
	{
		(*timer)->tv_usec = 1000000 + (*timer)->tv_usec;
		(*timer)->tv_sec ? (*timer)->tv_sec-- : 0;
	}
	printf("  Timer set for <%ld> seconds & <%d> microseconds\n",
	(*timer)->tv_sec, (*timer)->tv_usec);
}

static int32_t	compare(t_timeval *relative, t_timeval *time2)
{
	//printf("[TIME]\n  -- Compare --\n  time2 <%ld> seconds & <%d> microseconds\n  vs\n to relative-><%ld> seconds & <%d> microseconds\n", time2->tv_sec, time2->tv_usec, relative->tv_sec, relative->tv_usec);
	if ((relative->tv_sec > time2->tv_sec)
		|| (time2->tv_sec == relative->tv_sec && (relative->tv_usec >= time2->tv_usec)))
		return (1);
	return (0);
}

static void		setalarm(t_timeval *alarm, double factor)
{
	t_timeval	temp;
	double		interval;
	int64_t		i_interval;
	double		integer;
	int64_t		i_integer;

	gettimeofday(&temp, NULL);
	printf("[TIME]\n  -- Set Alarm --\n  It is <%ld> seconds & <%d> microseconds\n", temp.tv_sec, temp.tv_usec);
	interval = factor/server.simenv.timeinterval;
	integer = 0;
	if (interval > 1)
		interval = modf(interval, &integer);
	interval = (interval * 1000000);
	i_integer = (int64_t)integer;
	i_interval = (int64_t)interval;
	printf("  This is the interval now : %lld\n  This is the integer : %lld\n",
			i_interval, i_integer);
	alarm->tv_sec = temp.tv_sec + i_integer;
	while ((alarm->tv_usec = temp.tv_usec + i_interval) >= 1000000)
	{
		alarm->tv_usec -= 1000000;
		i_interval -= 1000000;
		alarm->tv_sec++;
	}
	printf("  Alarm at <%ld> seconds & <%d> microseconds\n",
			alarm->tv_sec, alarm->tv_usec);
}
