/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 16:19:45 by gnyssens          #+#    #+#             */
/*   Updated: 2024/08/20 14:22:35 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_first_cmd(char **av, char **cmd_args, int *pipe_fd, char **env)
{
	int		infile_fd;

	close(pipe_fd[0]);
	infile_fd = open(av[1], O_RDONLY);
	if (-1 == infile_fd)
		open_error();
	if (dup2(infile_fd, 0) == -1)
		dup2_error();
	if (dup2(pipe_fd[1], 1) == -1)
		dup2_error();
	close(infile_fd);
	close(pipe_fd[1]);
	if (execve(cmd_args[0], cmd_args, env) == -1)
	{
		free_split(cmd_args);
		perror("execve failed, probably non-existent option for command\n");
		exit(EXIT_FAILURE);
	}
}

void	handle_sec_cmd(char **av, char **cmd_args, int *pipe_fd, char **env)
{
	int		outfile_fd;

	close(pipe_fd[1]);
	outfile_fd = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (-1 == outfile_fd)
	{
		perror("second opening of second file failed !");
		exit(EXIT_FAILURE);
	}
	if (dup2(pipe_fd[0], 0) == -1)
		dup2_error();
	if (dup2(outfile_fd, 1) == -1)
		dup2_error();
	close(outfile_fd);
	close(pipe_fd[0]);
	if (execve(cmd_args[0], cmd_args, env) == -1)
	{
		free_split(cmd_args);
		perror("execve failed, probably non-existent option for command\n");
		exit(EXIT_FAILURE);
	}
}

void	special_wait(t_main_var *v)
{
	int	i;

	i = 1;
	while (i >= 0)
	{
		waitpid(v->pid[i], NULL, 0);
		i--;
	}
}

int	main(int ac, char *av[], char *env[])
{
	t_main_var	v;

	parsing(ac, av, env);
	v.args_cmd1 = find_path_command(av[2], env);
	v.args_cmd2 = find_path_command(av[3], env);
	if (NULL == v.args_cmd1 || NULL == v.args_cmd2)
		error_exit();
	if (pipe(v.pipe_fd) == -1)
		return (multi_free_split(v.args_cmd1, v.args_cmd2), 1);
	v.pid[0] = fork();
	if (-1 == v.pid[0])
		return (multi_free_split(v.args_cmd1, v.args_cmd2), 1);
	if (0 == v.pid[0])
		handle_first_cmd(av, v.args_cmd1, v.pipe_fd, env);
	v.pid[1] = fork();
	if (v.pid[1] != 0)
		close_fds(v.pipe_fd);
	if (-1 == v.pid[1])
		return (multi_free_split(v.args_cmd1, v.args_cmd2), 1);
	if (0 == v.pid[1])
		handle_sec_cmd(av, v.args_cmd2, v.pipe_fd, env);
	special_wait(&v);
	multi_free_split(v.args_cmd1, v.args_cmd2);
	return (0);
}
