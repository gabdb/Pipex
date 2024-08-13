/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 18:33:03 by gnyssens          #+#    #+#             */
/*   Updated: 2024/08/13 23:35:02 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//p-e en faire un char * qui ré-envoi le résultat de find_full_path
void	parsing(int ac, char *av[], char *env[])
{
	int	fd;

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
