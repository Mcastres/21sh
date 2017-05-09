/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastres <mcastres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 11:46:42 by mcastres          #+#    #+#             */
/*   Updated: 2017/04/28 14:13:53 by mcastres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	manage_simple_r(char **commands, int fd, t_shell **shell)
{
	char	**temp;
	pid_t	father;
	char	*tmp;
	int		i;
	t_shell	*s;

	i = -1;
	temp = NULL;
	s = *shell;
	close(STDOUT);
	dup2(fd, STDOUT);
	i = -1;
	while (ft_strcmp(commands[++i], ">") != 0)
		temp = ft_tabpushback(temp, commands[i]);
	i += 1;
	while (commands[++i])
		temp = ft_tabpushback(temp, commands[i]);
	if (!(s->path))
		return (0);
	i = 0;
	while (s->path && (s->path)[i])
	{
		tmp = ft_free_join(ft_strjoin((s->path)[i], "/"), temp[0], 'L');
		if (access(tmp, F_OK) == 0)
		{
			father = fork();
			if (father > 0)
				wait(0);
			if (father == 0)
			{
				if (is_redirection(temp))
					do_redirection(temp, &s);
				else if (!is_pipe(temp, &s))
					execve(tmp, temp, s->env);
			}
			ft_strdel(&tmp);
			break ;
		}
		ft_strdel(&tmp);
		i++;
	}
	exit(EXIT_FAILURE);
}

int		do_redirection(char **commands, t_shell **shell)
{
	int		fd;
	int		i;
	pid_t 	father;
	t_shell	*s;

	i = 0;
	s = *shell;
	while (ft_strcmp(commands[i], ">") != 0)
		i++;
	fd = open(commands[i + 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if ((father = fork()) == -1)
	{
		close(fd);
		exit(EXIT_FAILURE);
	}
	else if (!father)
		manage_simple_r(commands, fd, &s);
	close(fd);
	wait(0);
	return (1);
}

int		is_redirection(char **commands)
{
	int		i;

	i = 0;
	while (commands[i])
	{
		if (ft_strcmp(commands[i], ">") == 0)
		{
			if (commands[i - 1] && commands[i + 1])
				return (1);
		}
		i++;
	}
	return (0);
}
