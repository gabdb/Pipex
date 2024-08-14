/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 16:24:00 by gnyssens          #+#    #+#             */
/*   Updated: 2024/08/14 19:54:46 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../libft/ft_printf.h"
#include "../libft/get_next_line.h"

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

// PARSE
void	parsing(int ac, char *av[], char *env[]);

// PATH
char	*find_path(char *env[]);
char	*find_path_command(char *cmd, char *env[]);

// SUPPORT F
void	free_split(char **mem);
void	error_exit(void);
void	free_paths(char *path1, char *path2);
void	open_error(void);
void	dup2_error(void);