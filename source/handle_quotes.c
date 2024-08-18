/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 17:51:39 by gnyssens          #+#    #+#             */
/*   Updated: 2024/08/18 18:11:32 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_quotes(char *cmd)
{
	int	i;
	int	save;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == 39)
		{
			save = i;
			i++;
			while (cmd[i])
			{
				if (cmd[i] == 39 && cmd[i - 1] != ' ')
				{
					cmd[save] = ' ';
					cmd[i] = ' ';
					return ;
				}
				i++;
			}
			return ;
		}
		i++;
	}
}
