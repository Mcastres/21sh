/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_commande.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmadad <hmadad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 12:39:10 by hmadad            #+#    #+#             */
/*   Updated: 2017/04/28 13:20:13 by mcastres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_special_commande(t_shell **shell, char *commande)
{
	t_shell *s;

	s = *shell;
	if (ft_strcmp(commande, "cd") == 0)
		ft_prepare_cd(s->opt, &(s->env));
	else if (ft_strcmp(commande, "env") == 0)
		ft_strtab(s->env);
	else if (ft_strcmp(commande, "setenv") == 0)
		ft_prepare_setenv(&(s->env), s->opt);
	else if (ft_strcmp(commande, "unsetenv") == 0)
		ft_prepare_unsetenv(&(s->env), s->opt);
	else if (ft_strcmp(commande, "exit") == 0)
		ft_exit(shell);
	else if (ft_strcmp(commande, "echo") == 0)
		ft_echo(s->opt, &(s->env));
	else
		return (0);
	return (1);
}

void	ft_process2(t_shell **shell, char *commande)
{
	t_shell	*s;
	char	*tmp;
	int		i;

	s = *shell;
	i = 0;
	s->path = ft_strsplit(commande, ':');
	while ((s->all)[i])
	{
		s->opt = ft_strsplit(s->all[i], ' ');

		if (is_redirection(s->opt))
			do_redirection(s->opt, &s);
		if (!is_pipe(s->opt, &s) && !is_redirection(s->opt))
		{
			tmp = ft_strtrim((s->all)[i]);
			if (!(commande = ft_strbchr(tmp, ' ')))
				commande = ft_strtrim((s->all)[i]);
			if (ft_special_commande(shell, commande) == 0)
				ft_check_commande(shell, commande);
			if (tmp)
				ft_strdel(&tmp);
			ft_strdel(&commande);
			if (s->opt)
				ft_freetab(&(s->opt));
		}
		i++;
	}
	if (s->path)
		ft_freetab(&(s->path));
}

void	ft_process(t_shell **shell)
{
	t_shell	*s;
	char	*commande;

	s = *shell;
	if (ft_strcmp(s->line, "exit") == 0)
		ft_exit(shell);
	commande = ft_getenv(s->env, "PATH");
	s->all = ft_strsplit(s->line, ';');
	ft_process2(shell, commande);
	ft_freetab(&(s->all));
}

void	ft_exec_commande(t_shell **shell)
{
	t_shell	*s;
	char	*tmp;

	s = *shell;
	if (!s->line)
		return ;
	while (ft_strchr(s->line, '~') && (tmp = ft_getenv(s->env, "HOME")))
		s->line = ft_change_home_sign(s->line, tmp, '~');
	if (ft_strcmp(s->line, "") != 0 && ft_strcmp(s->line, "\n") != 0)
		ft_process(shell);
	ft_strdel(&(s->line));
}
