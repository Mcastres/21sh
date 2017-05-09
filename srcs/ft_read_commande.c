/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_commande.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmadad <hmadad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 17:00:05 by hmadad            #+#    #+#             */
/*   Updated: 2017/04/27 12:01:56 by mcastres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_escape(t_shell **shell)
{
	t_shell	*s;

	s = *shell;
	ft_putstr("\n");
	ft_putstr(RED "-~[ Fermeture du Terminal ]~-\n" RESET);
	tcsetattr(0, TCSADRAIN, &(s->default_term));
	exit(0);
}

void	ft_reset_pos(t_shell **shell)
{
	t_shell	*s;

	s = *shell;
	s->position = 0;
	s->pos_max = 0;
}

void	ft_update_history(t_shell **shell)
{
	int			fd;
	t_shell		*s;
	char		*tmp;

	s = *shell;
	tmp = ft_strtrim(s->line);
	s->line = ft_strtrimb(tmp);
	if (tmp && ft_strcmp(tmp, "") != 0)
	{
		if ((fd = open(".history", O_WRONLY | O_APPEND)) == -1)
			ft_putstr("Cannot open file\n");
		else
		{
			ft_putendl_fd(s->line, fd);
			close(fd);
		}
		ft_liste_push_front(&(s->history), ft_listenew(s->line));		//Ici
		ft_strdel(&tmp);
	}
}

void	ft_read_commande(t_shell **shell)
{
	t_shell		*s;
	char		buf[5];

	s = *shell;
	while (42)
	{
		ft_bzero(buf, 5);
		read(0, buf, 4);
		if (ft_strcmp(buf, "\n") == 0)
		{
			ft_putchar('\n');
			if (s->line)
			{
				if (ft_dquote(s->line))
					ft_dodquote(&s);
				else if (ft_quote(s->line))
					ft_doquote(&s);
			}
			ft_update_history(&s);
			ft_exec_commande(shell);
			ft_strdel(&(s->line));
			ft_prompt(s->env);
			ft_reset_pos(shell);
			s->s_h = 0;
		}
		else if (buf[0] == 27 && ft_strlen(buf) == 3 && buf[2] != '3')
			ft_history_key(shell, buf);
		else if (buf[0] == 27 && ft_strlen(buf) == 1)
			ft_escape(shell);
		else if (buf[0] == 127 || (buf[0] == 27 && buf[2] == '3'))
			ft_delete_char(shell, buf);
		else
			ft_print_char(shell, buf);
	}
}
