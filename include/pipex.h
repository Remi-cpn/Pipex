/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 10:35:30 by rcompain          #+#    #+#             */
/*   Updated: 2026/01/20 11:41:54 by rcompain         ###   ########.fr       */
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
	FAILURE = -1,
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

void	child_process_first(t_data *pipex);
void	child_process_last(t_data *pipex);

/* EXIT */
void	exit_prog(t_data *pipex, int code_error);
void	free_array(char **s);

#endif
