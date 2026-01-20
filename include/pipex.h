/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 10:35:30 by rcompain          #+#    #+#             */
/*   Updated: 2026/01/20 15:34:42 by rcompain         ###   ########.fr       */
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
	int		nbr_cmd;
	char	***cmd;
	char	*outfile;
	char	*path;
	char	**envp;
	int		**fds;
	int		nbr_fds;
	pid_t	pid;
}	t_data;

void	child_process_first(t_data *pipex);
void	child_process(t_data *pipex, char **cmd, int i);
void	child_process_last(t_data *pipex);

/* EXIT */
void	exit_prog(t_data *pipex, int code_error);
void	free_array(char **s);

#endif
