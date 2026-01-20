/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 10:36:24 by rcompain          #+#    #+#             */
/*   Updated: 2026/01/18 10:49:09 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	init_data(t_data *data, char **av)
{
	data->infile = av[1];
	data->cmd1 = ft_split(av[2], ' ');
	data->cmd2 = ft_split(av[3], ' ');
	data->outfile = av[4];
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;
	pid_t	pid1;
	pid_t	pid2;

	if (ac != 5)
		exit_prog("ERROR Arg");
	init_data(&data, av);
	data.envp = envp;
	pipe(data.fds);
	pid1 = fork();
	if (pid1 == CHILD)
		child_process_cmd1(&data);
	pid2 = fork();
	if (pid2 == CHILD)
		child_process_cmd2(&data);
	close(data.fds[0]);
	close(data.fds[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
