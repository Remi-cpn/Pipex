/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 11:00:59 by rcompain          #+#    #+#             */
/*   Updated: 2026/01/20 12:30:49 by rcompain         ###   ########.fr       */
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

void	exit_prog(t_data *pipex, int code_error)
{
	int	i;

	if (code_error != SUCCES)
		perror("Error ");
	i = 0;
	while (pipex->cmd[i])
	{
		free_array(pipex->cmd[i]);
		i++;
	}
	exit(code_error);
}
