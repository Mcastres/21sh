/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipette.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastres <mcastres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 11:46:42 by mcastres          #+#    #+#             */
/*   Updated: 2017/04/28 13:35:35 by mcastres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	execute_pipe(char **commands, t_shell **shell)
{
	char	*tmp;
	pid_t	father;
	int		i;
	t_shell *s;

	s = *shell;
	if (!(s->path))
		return ;
	i = 0;
	while (s->path && (s->path)[i])
	{
		tmp = ft_free_join(ft_strjoin((s->path)[i], "/"), commands[0], 'L');
		if (access(tmp, F_OK) == 0)
		{
			father = fork();
			if (father > 0)
				wait(0);
			if (father == 0)
				execve(tmp, commands, s->env);
			ft_strdel(&tmp);
			break ;
		}
		ft_strdel(&tmp);
		i++;
	}
}

static int		manage_pipe(char ***commands, int fd_in, \
	int p[], t_shell **shell)
{
	t_shell		*s;

	s = *shell;
	dup2(fd_in, 0);
	if (*(commands + 1) != NULL)
		dup2(p[1], 1);
	close(p[0]);
	execute_pipe(*commands, &s);
	exit(EXIT_FAILURE);
}

static int		do_pipe(char ***commands, t_shell **shell, int fd_in)
{
	int   		p[2];
	pid_t 		father;
	t_shell 	*s;

	s = *shell;
	while (*commands != NULL)
	{
		pipe(p);
		if ((father = fork()) == -1)
			exit(EXIT_FAILURE);
		else if (father == 0)
			manage_pipe(commands, fd_in, p, &s);
		else
		{
			wait(0);
			close(p[1]);
			fd_in = p[0];
			commands++;
		}
	}
	return (1);
}

// static char		**parse_redirect(char ***commands, int n)
// {
// 	char	**hamza;
// 	int		i;
//
// 	i = -1;
// 	hamza = NULL;
// 	while (commands[n][++i])
// 	{
// 		if (ft_strcmp(commands[n][i], ">") != 0
// 		&& ft_strcmp(commands[n][i], "<") != 0
// 		&& ft_strcmp(commands[n][i], ">>") != 0
// 		&& ft_strcmp(commands[n][i], "<<") != 0)
// 			hamza = ft_tabpushback(hamza, commands[n][i]);
// 		else
// 			break;
// 	}
// 	return (hamza);
// }

static int		parse_pipe(char **commands, t_shell **shell)
{
	t_shell			*s;
	char			***pipe;
	char			**temp;
	static int		i;

	i = 0;
	s = *shell;
	pipe = NULL;
	while (commands[i])
	{
		temp = NULL;
		while (commands[i] && ft_strcmp(commands[i], "|") != 0)
		{
			if (ft_strcmp(commands[i], ">") == 0)
				break ;
			temp = ft_tabpushback(temp, commands[i]);
			i++;
		}
		pipe = ft_tabbpushback(pipe, temp);
		if (commands[i])
			i++;
	}
	// pipe[0] = ft_tabdup(parse_redirect(pipe, 0));
	// pipe[1] = ft_tabdup(parse_redirect(pipe, 1));
	do_pipe(pipe, &s, 0);
	ft_freetabb(pipe, ft_tabblen(pipe));
	return (1);
}

int		is_pipe(char **commands, t_shell **shell)
{
	t_shell	*s;
	int		i;

	i = 0;
	s = *shell;
	while (commands[i])
	{
		if (ft_strchr(commands[i], '|'))
		{
			if (commands[i - 1] && commands[i + 1])
				return (parse_pipe(commands, &s));
		}
		i++;
	}
	return (0);
}
