/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmadad <hmadad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 17:00:05 by hmadad            #+#    #+#             */
/*   Updated: 2017/04/27 12:01:23 by mcastres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int 	ft_dquote(char *str)
{
	size_t i = 0;
	int count = 0;

	while (i < ft_strlen(str))
	{
		if (str[i] == '"')
			count++;
		i++;
	}
	return (count %2 != 0);
}

int 	ft_quote(char *str)
{
	size_t i = 0;
	int count = 0;

	while (i < ft_strlen(str))
	{
		if (str[i] == '\'')
			count++;
		i++;
	}
	return (count %2 != 0);
}

void 	ft_dodquote(t_shell **shell)
{
	char 	buffer[5];
	char 	*temp;
	t_shell	*s;

	temp = "\n";
	s = *shell;
	ft_putstr("dquote> ");
	while (1)
	{
		ft_bzero(buffer, 5);
		read(0, buffer, 4);
		ft_putstr(buffer);
		if (ft_strcmp(buffer, "\n") == 0 && !ft_dquote(temp))
			ft_putstr("dquote> ");
		temp = ft_strjoin(temp, buffer);
		if (ft_strcmp(buffer, "\n") == 0 && ft_dquote(temp))
			break;
	}
	temp = ft_strtrim_c(temp, '"');
	s->line = ft_strjoin(ft_strtrim_c(s->line, '"'), temp);
}

void 	ft_doquote(t_shell **shell)
{
	char 	buffer[5];
	char 	*temp;
	t_shell	*s;

	temp = "\n";
	s = *shell;
	ft_putstr("quote> ");
	while (1)
	{
		ft_bzero(buffer, 5);
		read(0, buffer, 4);
		ft_putstr(buffer);
		if (ft_strcmp(buffer, "\n") == 0 && !ft_quote(temp))
			ft_putstr("quote> ");
		temp = ft_strjoin(temp, buffer);
		if (ft_strcmp(buffer, "\n") == 0 && ft_quote(temp))
			break;
	}
	temp = ft_strtrim_c(temp, '\'');
	s->line = ft_strjoin(ft_strtrim_c(s->line, '\''), temp);
}
