/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 10:36:24 by rcompain          #+#    #+#             */
/*   Updated: 2026/01/16 13:11:30 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 5)
		exit_prog("ERROR Arg\n");
	data.infile = av[1];
	data.cmd1 = av[2];
	data.cmd2 = av[3];
	data.outfile = av[4];
	return (0);
}
