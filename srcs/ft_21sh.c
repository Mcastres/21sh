/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmadad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 15:43:27 by hmadad            #+#    #+#             */
/*   Updated: 2017/03/15 15:57:47 by hmadad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_21sh(char ***env)
{
	t_shell		*shell;

	if (!(shell = (t_shell *)malloc(sizeof(t_shell))))
		return (0);
	shell->env = *env;
	shell->history = ft_init_term(&shell);
	ft_prompt(*env);
	ft_read_commande(&shell);
	return (1);
}
