/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 10:53:55 by nkouris           #+#    #+#             */
/*   Updated: 2018/06/14 16:55:37 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "universal.h"
#include "time.h"
#include "events.h"
#include "death.h"

static int32_t	compare(t_timeval *relative, t_timeval *time2);
static void		settimer(t_timeval **timer);
static void		setalarm(t_timeval *alarm, float factor);

__attribute__((constructor))void	construct_time(void)
{
	time.compare = &compare;
	time.settimer = &settimer;
	time.setalarm = &setalarm;
}

static int32_t	compare(t_timeval *relative, t_timeval *time2)
{
	printf("[TIME]\n  -- Compare --\n  time2 <%ld> seconds & <%d> microseconds\n  vs\n to relative-><%ld> seconds & <%d> microseconds\n", time2->tv_sec, time2->tv_usec, relative->tv_sec, relative->tv_usec);
	if ((relative->tv_sec > time2->tv_sec)
		|| (time2->tv_sec == relative->tv_sec && (relative->tv_usec >= time2->tv_usec)))
	{
		printf("  Too much time has passed relative->n");
		return (1);
	}
	return (0);
}


static t_timeval	*deathcompare(void)
{
	if (!(death.track.players->first)
		&& !(death.track.eggs->first))
		return (NULL);
	if (!(death.track.players->first))
		return (&(((t_egg *)(death.track.eggs->first->data))->alarm));
	if (!(death.track.eggs->first))
		return (&((t_player *)(death.track.players->first->data))->alarm);
	if (time.compare(&(((t_egg *)(death.track.eggs->first->data))->alarm),
					&(((t_player *)(death.track.players->first->data))->alarm)))
		return (&((t_player *)(death.track.players->first->data))->alarm);
	else
		return (&(((t_egg *)(death.track.eggs->first->data))->alarm));
	return (NULL);
}

static t_timeval	*nearestalarm(void)
{
	t_timeval	*nearestdeath;

	nearestdeath = deathcompare();
	if (!(event.queue.data->first)
		&& !(nearestdeath))
		return (NULL);
	if (!(event.queue.data->first))
		return (nearestdeath);
	if (!(nearestdeath))
		return (&(((t_event *)(event.queue.data->first->data))->alarm));
	if (time.compare(&(((t_event *)(event.queue.data->first->data))->alarm),
					nearestdeath))
		return (nearestdeath);
	else
		return (&(((t_event *)(event.queue.data->first->data))->alarm));
	return (NULL);
}

static void		settimer(t_timeval **timer)
{
	t_timeval	temp;
	t_timeval	*alarm;

	gettimeofday(&temp, NULL);
	printf("[TIME]\n  It is <%ld> seconds & <%d> microseconds\n", temp.tv_sec, temp.tv_usec);
	if (!(alarm = nearestalarm()))
	{
		if (*timer)
			ft_memdel((void **)timer);
		printf("  No events to check\n");
	}
	else
	{
		if (!(*timer))
			(*timer) = (t_timeval *)calloc(1, sizeof(t_timeval));
	printf("  Alarm pulled : <%ld> seconds & <%d> microseconds\n", alarm->tv_sec, alarm->tv_usec);
		(*timer)->tv_sec = alarm->tv_sec - temp.tv_sec;
		if (alarm->tv_usec > temp.tv_usec)
			(*timer)->tv_usec = alarm->tv_usec - temp.tv_usec;
		else
			(*timer)->tv_usec = alarm->tv_usec;
		printf("  Timer set for <%ld> seconds & <%d> microseconds\n", (*timer)->tv_sec, (*timer)->tv_usec);
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
	printf("[TIME]\n  -- Set Alarm --\n  It is <%ld> seconds & <%d> microseconds\n", temp.tv_sec, temp.tv_usec);
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
	printf("  Alarm at <%ld> seconds & <%d> microseconds\n", alarm->tv_sec, alarm->tv_usec);
}
