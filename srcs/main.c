/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmadad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 14:40:50 by hmadad            #+#    #+#             */
/*   Updated: 2017/03/31 13:10:17 by hmadad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		main(int ac, char **av, char **env)
{
	char	**e;

	(void)ac;
	(void)av;
	e = ft_duptab2d(env);
	ft_21sh(&e);
	return (0);
}
