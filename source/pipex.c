/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 16:19:45 by gnyssens          #+#    #+#             */
/*   Updated: 2024/08/16 19:17:59 by gnyssens         ###   ########.fr       */
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
	if (dup2(infile_fd, 0) == -1) //stdinput redirected to infile
		dup2_error();
	if (dup2(pipe_fd[1], 1) == -1) //stdoutput redirected to write-end pipe
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
	//else
	//	write(1, "DEUXIEME OUVERTURE MARCHE\n", 26);
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

int main(int ac, char *av[], char *env[])
{
	int		pid;
	int		pipe_fd[2];
    char	**args_cmd1;
	char	**args_cmd2;

	parsing(ac, av, env);
	args_cmd1 = find_path_command(av[2], env);
	args_cmd2 = find_path_command(av[3], env);
	if (NULL == args_cmd1 || NULL == args_cmd2)
		error_exit();
	if (pipe(pipe_fd) == -1)
		return (free_split(args_cmd1), free_split(args_cmd2), write(1, "error pipe\n", 11), 1);
	pid = fork();
	if (-1 == pid)
		return (free_split(args_cmd1), free_split(args_cmd2), write(1, "error fork\n", 11), 1);
	if (0 == pid)
		handle_first_cmd(av, args_cmd1, pipe_fd, env);
	wait(NULL);
	pid = fork();
	if (pid != 0)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
	if (-1 == pid)
		return (free_split(args_cmd1), free_split(args_cmd2), write(1, "error fork\n", 11), 1);
	if (0 == pid)
		handle_sec_cmd(av, args_cmd2, pipe_fd, env);
	wait(NULL);
	free_split(args_cmd1);
	free_split(args_cmd2);
	return (0);
}

/*


//program for: cat infile | grep Lausanne


int main(int ac, char *av[], char *env[])
{
    int     fd[2];
    int     pid;
    int     file_fd;
    char    *cat_args[] = {"/bin/cat", NULL};
    char    *grep_args[] = {"/usr/bin/grep", "Lausanne", NULL};

    pipe(fd);
    pid = fork();
    if (pid == 0)
    {
        close(fd[0]);
        file_fd = open("infile.txt", O_RDONLY);
        dup2(file_fd, 0); //cat will read from infile.txt instead of standard keyboard
        dup2(fd[1], 1); //cat's output will be send into write_end of pipe instead of console
        close(fd[1]);
        execve("/bin/cat", cat_args, env);
    }
    else
    {
        close(fd[1]);
        dup2(fd[0], 0);
        close(fd[0]);
        execve("/usr/bin/grep", grep_args, env);
    }

    return (0);
}
*/