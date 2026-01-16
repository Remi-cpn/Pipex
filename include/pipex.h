/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 10:35:30 by rcompain          #+#    #+#             */
/*   Updated: 2026/01/16 13:11:34 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include "stdlib.h"
# include "unistd.h"

typedef struct s_data
{
	char	*infile;
	char	*cmd1;
	char	*cmd2;
	char	*outfile;
}	t_data;


/* EXIT */
void	exit_prog(char *str);

#endif
