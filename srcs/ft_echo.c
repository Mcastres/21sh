/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmadad <hmadad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 11:21:14 by hmadad            #+#    #+#             */
/*   Updated: 2017/04/25 13:00:39 by mcastres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		ft_echo(char **opt, char ***g_env)
{
	char	*temp;
	int		i;

	i = 1;
	if (ft_strlen2d(opt) > 1)
		while (opt[i])
		{
			if (opt[i][0] == '$')
			{
				if (ft_getenv(*g_env, opt[i] + 1))
					ft_putstr(ft_getenv(*g_env, opt[i] + 1));
				else
					ft_putstr(opt[i]);
			}
			else
			{
				temp = ft_escapequote(opt[i]);
				ft_putstr(temp);
				ft_strdel(&temp);
			}
			ft_putchar(' ');
			i++;
		}
	ft_putchar('\n');
}
