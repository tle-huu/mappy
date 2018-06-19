/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zappy_prototypes.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 03:41:58 by psprawka          #+#    #+#             */
/*   Updated: 2018/06/19 02:15:35 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZAPPY_PROTOTYPES_H
# define ZAPPY_PROTOTYPES_H

# include "zappy.h"

/*
**	client.c
*/
void			client_death(int clientfd);
void			new_client(void);

/*
**	execute.c
*/
int				execute_events(void);

/*
**	event.c
*/
t_event			*init_event(void *entity, struct timeval *time, int (*fct)(void *, char *), char *msg);
struct timeval	*event_time(void *entity, int type, int itable);
int				add_event(void *entity, int type, int itable, char *msg);

/*
**	handle/
*/
int				handle_recv(int fd);
int				handle_ai(int fd, char *msg);
int 			handle_graphic(int fd, char *msg);
int 			handle_nondef(int fd, char *msg);

/*
**	init/
*/
int				init_server(void);
int				init_server_socket(void);
t_player		*init_player(int sockfd);
int				init_map(void);

/*
**	main.c
*/
int				main_game_loop(void);
int				main(int ac, char **av);

/*
**	parse/
*/
int				opt_print_queue(char **av, int *i);
int				opt_port(char **av, int *i);
int				opt_dimentions(char **av, int *i);
int				opt_max_players(char **av, int *i);
int				opt_time(char **av, int *i);
int				opt_teams(char **av, int *i);
int				validate_args(void);
int				parse_args(int ac, char **av);

/*
**	queue.c
*/
void			remove_node(t_queue **queue, t_node *prev, t_node *remove);
void			clean_queue(int fd);

/*
**	teams.c
*/
int				get_team_number(int clientfd, char *msg);
void			assign_team(int	clientfd, int team_nb);

/*
**	time.c
*/
int				time_compare(struct timeval *first, struct timeval *second);
int				time_compare_events(t_node *node1, t_node *node2);
struct timeval	*set_time_alarm(void);

/*
**	generator.c
*/
void			generate_ressource(int ressource);
void			init_map_ressource(void);

/*
**	fork/eggs.c
*/
t_egg			*new_egg(t_player *player);
int				add_egg_team(t_egg *egg, t_team *team);
int				handle_egg(t_player *player);

/*
**	tools/
*/
int				tools_world_dimensions(t_player *player);
int				error(int errnb, char *msg, bool ifailure);
int				rand_direction(void);
void			rand_position(t_player *player);
void			*lookup_clients(int fd);
uint32_t		ft_modulo(int k, int n);
int				graphic_direction(int direction);

/*
**	free.c
*/
void			free_event(t_event *event);
void			free_player(int fd);

#endif
