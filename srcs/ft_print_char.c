/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmadad <hmadad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 12:44:02 by hmadad            #+#    #+#             */
/*   Updated: 2017/04/25 12:39:28 by mcastres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	ft_line_exist(t_shell **shell, char *buf)
{
	int		len;
	t_shell	*s;

	s = *shell;
	if (s->position == s->pos_max)
	{
		s->line = ft_free_join(s->line, buf, 'L');
		ft_putstr(buf);
	}
	else
	{
		len = s->pos_max - (s->pos_max - s->position);
		while (len)
		{
			tputs(tgetstr("le", NULL), 0, ft_putc);
			len--;
		}
		tputs(tgetstr("cd", NULL), 0, ft_putc);
		s->line = ft_straddat(s->line, buf[0], s->position);
		ft_putstr(s->line);
	}
}

void	ft_print_char(t_shell **shell, char *buf)
{
	t_shell	*s;

	s = *shell;
	if (s->line)
		ft_line_exist(shell, buf);
	else
	{
		s->line = ft_strdup(buf);
		ft_putstr(buf);
	}
	s->pos_max += 1;
	s->position += 1;
}
