/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 22:52:11 by gnyssens          #+#    #+#             */
/*   Updated: 2024/08/16 19:16:25 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// donne ce qu'il y a après PATH=
char	*find_paths(char *env[])
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (*(env + i) + 5); //addresse du string PATH=... + 5 pr skipper `PATH=`
		i++;
	}
	return (perror("problem: PATH env' variable not found !\n"), NULL);
}

//splitter "ls -l" en {""}
char	**split_command(char *cmd)
{
	char	*command; //cmd avec '/' au debut
	char	**result;

	command = ft_strjoin("/", cmd);
	if (!command)
	{
		perror("strjoin failed\n");
		exit(EXIT_FAILURE);
	}
	result = ft_split(command, ' ');
	if (!result)
	{
		perror("split failed\n");
		exit(EXIT_FAILURE);
	}
	free(command);
	return (result);
}

//returns correct path for a command
char	**find_path_command(char *cmd, char *env[])
{
	int		i;
	char	*paths; //(PATH=)... : ... : ...
	char	**split_path;
	char	*check; //append cmd to path and check for existence
	char	**command; //split de la commande avec ses options (genre "ls -l")

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
			*(command) = ft_strdup(check); //ici pas protect.
			free(check);
			free_split(split_path);
			return (command);
		}
		free(check);
		i++;
	}
	return (free_split(split_path), free_split(command), NULL); //commande nexiste pas -> free tout, perror and exit !
}
