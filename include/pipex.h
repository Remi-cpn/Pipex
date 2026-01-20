/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 10:35:30 by rcompain          #+#    #+#             */
/*   Updated: 2026/01/18 10:49:52 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>

typedef enum s_error
{
	ERROR = 1,
	FAILURE = 1,
	SUCCES = 0,
}	t_error;

typedef enum s_fork
{
	CHILD = 0,
}	t_fork;

typedef struct s_data
{
	char	*infile;
	char	**cmd1;
	char	**cmd2;
	char	*outfile;
	char	*path;
	char	**envp;
	int		fds[2];
	pid_t	pid;
}	t_data;

void	child_process_cmd1(t_data *data);
void	child_process_cmd2(t_data *data);

/* EXIT */
void	exit_prog(char *str);
void	free_array(char **s);

#endif
