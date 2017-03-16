/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cursor_position.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmadad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 11:42:08 by hmadad            #+#    #+#             */
/*   Updated: 2017/03/16 13:28:09 by hmadad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_reset_position(t_shell **shell)
{
	t_shell	*s;

	s = *shell;
	s->position = 0;
	s->pos_max = 0;
}
