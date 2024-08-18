/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 22:52:11 by gnyssens          #+#    #+#             */
/*   Updated: 2024/08/18 18:07:55 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_paths(char *env[])
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (*(env + i) + 5);
		i++;
	}
	return (perror("problem: PATH env' variable not found !\n"), NULL);
}

char	**split_command(char *cmd)
{
	char	*command;
	char	**result;

	command = ft_strjoin("/", cmd);
	if (!command)
	{
		perror("strjoin failed\n");
		exit(EXIT_FAILURE);
	}
	printf("%s\n", command);
	handle_quotes(command);
	printf("%s\n", command);
	result = ft_split(command, ' ');
	if (!result)
	{
		perror("split failed\n");
		exit(EXIT_FAILURE);
	}
	free(command);
	return (result);
}

char	**find_path_command(char *cmd, char *env[])
{
	int		i;
	char	*paths;
	char	**split_path;
	char	*check;
	char	**command;

	paths = find_paths(env);
	split_path = ft_split(paths, ':');
	command = split_command(cmd);
	i = 0;
	while (split_path[i] != NULL)
	{
		check = ft_strjoin(split_path[i], command[0]);
		if (access(check, X_OK) == 0)
		{
			free(command[0]);
			*(command) = safe_strdup(check);
			free(check);
			free_split(split_path);
			return (command);
		}
		free(check);
		i++;
	}
	return (free_split(split_path), free_split(command), NULL);
}
