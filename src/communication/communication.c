/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   communication.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 14:11:03 by nkouris           #+#    #+#             */
/*   Updated: 2018/08/11 19:14:59 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "graphics.h"
#include "client.h"
#include "vehicle.h"
#include "transmit.h"
#include "communication.h"

/* method function prototypes */
static int32_t	outgoing(int32_t cl, char *str);
static int32_t	incoming(int32_t cl);
static int32_t	printraw(void);
static int32_t	newclient(int32_t cl);
static int32_t	vehicles(t_vehicle *vl, void *datagram, int8_t);
static int32_t	graphical(t_graphic *gr, char *str);

__attribute__((constructor))void	construct_communication(void)
{
	communication.outgoing = &outgoing;
	communication.incoming = &incoming;
	communication.printraw = &printraw;
	communication.graphical = &graphical;
	communication.vehicles = &vehicles;
	communication.newclient = &newclient;
}

static int32_t	newclient(int32_t cl)
{
	if (communication.incoming(cl) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (ft_strequ(server.recvbuf, "GRAPHIC\n"))
		server.clients.status[cl] = JOINGRAPHIC;
	else
		server.clients.status[cl] = JOINVEHICLE;
	return (EXIT_SUCCESS);
}

static int32_t	incoming(int32_t cl)
{
	int32_t		ret;

	//printf("Recieving message from client <%d>\n", cl);
	bzero(server.recvbuf, 512);
	//printf("Recv buffer zeroed\n");
	if ((ret = recv(cl, server.recvbuf, 512, 0)) < 0)
		return (EXIT_FAILURE);
	else if (!ret)
	{
		client.disconnect(cl);
		return (-1);
	}
	server.recvbuf[(ret)] = '\0';
	//printf("  This is the buffer recieved |%s|\n", server.recvbuf);
	return (EXIT_SUCCESS);
}

static int32_t	graphical(t_graphic *gr, char *str)
{
	t_dblist	*temp;

	if (!gr)
	{
		temp = graphic.data.first;
		while (temp)
		{
			gr = (t_graphic *)(temp->data);
			if (communication.outgoing(gr->c_fd, server.sendbuf) == EXIT_FAILURE
				|| server.flag == CLEPIPE)
			{
				server.flag = SIMULATE;
				client.crash(gr->c_fd);
			}
			temp = temp->next;
		}
	}
	else
	{
		if (communication.outgoing(gr->c_fd, str) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int32_t	vehicles(t_vehicle *vl, void *datagram, int8_t single)
{
	t_vehicle	*og;
	t_dblist	*temp;

	og = vl;
	temp = vehicle.data.first;
	if (!single)
	{
		while (temp)
		{
//			printf("Top of transmit.vehicles()\n");
			vl = (t_vehicle *)(temp->data);
			if (vl != og)
			{
				if (communication.outgoing(vl->c_fd, datagram) == EXIT_FAILURE
					|| server.flag == CLEPIPE)
				{
					server.flag = SIMULATE;
					client.crash(vl->c_fd);
				}
			}
			temp = temp->next;
//			printf("End of transmit.vehicles()\n");
		}
	}
	else
	{
		if (communication.outgoing(vl->c_fd, datagram) == EXIT_FAILURE
			|| server.flag == CLEPIPE)
		{
			printf("here\n");
			server.flag = SIMULATE;
			client.crash(vl->c_fd);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

static int32_t	outgoing(int32_t cl, char *str)
{
	if (send(cl, str, strlen(str), 0) < 0)
	{
		printf("\nOUTGOING FAILED\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int32_t	printraw(void)
{
	//printf("Unknown command, raw buffer of recieved message:\n\n|%s|\n\n",
		//	server.recvbuf);
	return (EXIT_SUCCESS);
}
