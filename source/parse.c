/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 18:33:03 by gnyssens          #+#    #+#             */
/*   Updated: 2024/08/19 16:30:10 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	multi_free_split(char **a, char **b)
{
	free_split(a);
	free_split(b);
}

void	close_fds(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

void	parsing(int ac, char *av[], char *env[])
{
	int	fd;

	(void)env;
	if (5 != ac)
	{
		perror("wrong number of arguments !");
		exit(EXIT_FAILURE);
	}
	if (access(av[1], F_OK | R_OK) == -1)
	{
		perror("access check file1 failed !");
		exit(EXIT_FAILURE);
	}
	fd = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (-1 == fd)
	{
		perror("file2 cannot be opened nor created !");
		exit(EXIT_FAILURE);
	}
	close(fd);
}

char	*safe_strdup(char *s)
{
	char	*result;

	result = ft_strdup(s);
	if (!result)
	{
		perror("malloc failed in strdup\n");
		exit(EXIT_FAILURE);
	}
	return (result);
}
