/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 10:35:30 by rcompain          #+#    #+#             */
/*   Updated: 2026/01/16 16:09:56 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include "stdlib.h"
# include "unistd.h"
//# include <sys/types.h>
# include <sys/wait.h>


typedef struct s_data
{
	char	*infile;
	char	**cmd1;
	char	**cmd2;
	char	*outfile;
	char	**envp;
	int		fds[2];
	pid_t	pid;
}	t_data;

/* EXIT */
void	exit_prog(char *str);

#endif
