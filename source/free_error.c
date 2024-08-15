/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support_funct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:07:58 by gnyssens          #+#    #+#             */
/*   Updated: 2024/08/14 19:54:38 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_exit(void)
{
	perror("non-existant command !");
	exit(EXIT_FAILURE);
}

void	free_split(char **mem)
{
	int	i;

	i = 0;
	while (mem[i] != NULL)
	{
		free(mem[i]);
		i++;
	}
	free(mem);
}

void	free_paths(char *path1, char *path2)
{
	free(path1);
	free(path2);
}

void	open_error(void)
{
	perror("open error !\n");
	exit(EXIT_FAILURE);
}

void	dup2_error(void)
{
	perror("dup2 failed !");
	exit(EXIT_FAILURE);
}