/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   configurator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 16:54:59 by nkouris           #+#    #+#             */
/*   Updated: 2018/05/29 09:51:23 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_server.h"

static int32_t	validate_server_password(t_servenv *server, char *buf)
{
	char	*temp;
	if (!(temp = ft_strchr(buf, '\n')))
	{
		ft_printf("Invalid password, please enter one that is less than 512 characters.\n");
		return (EXIT_FAILURE);
	}
	*temp = '\0';
#ifdef DEBUG
	ft_printf("write to file : \"%s\"\n", buf);
#endif
	write(server->pathfd, buf, ft_strlen(buf));
	ft_printf("Password set!\n");
	return (EXIT_SUCCESS);
}

static inline __attribute__((always_inline))void	set_silentterm(void)
{
	struct termios	term;

	ft_bzero(&term, sizeof(struct termios));
	tcgetattr(STDIN_FILENO, &term);
	if ((term.c_lflag & ECHO) == ECHO)
		term.c_lflag &= ~ECHO;
	else
		term.c_lflag |= ECHO;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);
}

static char	*ft_getenv(char *name, char **envp)
{
	int		i;
	char	*ret;

	i = 0;
	if (!name)
		return (NULL);
	while (envp[i])
	{
		if (!ft_strncmp(name, envp[i],
			((ret = ft_strchr(envp[i], '=')) - envp[i])))
			return (ret + 1);
		i++;
	}
	return (NULL);
}

static inline __attribute__((always_inline))int32_t	create_servepath(t_servenv *server,
		char **envp)
{
	char	*temp;

	server->setpath = ft_getenv("HOME", envp);
	if (!(temp = (char *)ft_memalloc(ft_strlen(server->setpath) + sizeof(SERVER_CONFIG) + 2)))
		return (EXIT_FAILURE);
	ft_strcpy(temp, server->setpath);
	ft_strcat(temp, "/");
	ft_strcat(temp, SERVER_CONFIG);
	server->setpath = temp;
#ifdef DEBUG
	ft_printf("path to check : \"%s\"\n", server->setpath);
#endif
	return (EXIT_SUCCESS);
}

int32_t		server_config(t_servenv *server, char **envp)
{
	char	buf[513];
	int32_t	ret;

	ret = EXIT_FAILURE;
	ft_bzero(buf, 513);
	if (create_servepath(server, envp) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if ((server->pathfd = open(server->setpath, (O_RDWR | O_APPEND))) < 0)
	{
		server->pathfd = open(server->setpath, (O_RDWR | O_APPEND | O_CREAT), 0644);
		while (ret == EXIT_FAILURE)
		{
			ft_printf("Please set the server password (using no more than 512 characters):\n");
			set_silentterm();
			read(STDIN_FILENO, buf, 512);
			set_silentterm();
			ret = validate_server_password(server, buf);
		}
	}
	return (EXIT_SUCCESS);
}
