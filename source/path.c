/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 22:52:11 by gnyssens          #+#    #+#             */
/*   Updated: 2024/08/14 19:16:26 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path(char *env[])
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

//returns correct path for a command
char	*find_path_command(char *cmd, char *env[])
{
	int		i;
	char	*path; //(PATH=)... : ... : ...
	char	**split_path;
	char	*check; //append cmd to path and check for existence
	char	*command; //commande complète (avec '/' au début en gros)

	path = find_path(env);
	split_path = ft_split(path, ':');
	command = ft_strjoin("/", cmd);
	i = 0;
	while (split_path[i] != NULL)
	{
		check = ft_strjoin(split_path[i], command);
		if (access(check, X_OK) == 0)
		{
			free(check);
			check = ft_strdup(split_path[i]); // used to return the correct path
			free_split(split_path);
			free(command);
			return (check);
		}
		else
			free(check);
		i++;
	}
	return (free_split(split_path), free(command), NULL); //commande nexiste pas -> free tout, perror and exit !
}
