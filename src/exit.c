/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 11:00:59 by rcompain          #+#    #+#             */
/*   Updated: 2026/01/18 11:13:58 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include <stdio.h>

void	free_array(char **s)
{
	int	i;

	i = 0;
	while (s && s[i])
		ft_freenull(s[i++]);
	ft_freenull(s);
}

void	exit_prog(char *str)
{
	write(2, "Error: ", 7);
	write(2, str, ft_strlen(str));
	exit(1);
}
