/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 16:19:45 by gnyssens          #+#    #+#             */
/*   Updated: 2024/08/14 20:10:43 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//jpense que le code aura un problème si la commande a un flag, genre "ls -l"
//find_full_path va sans doute buger, à vérifier

//encore le problème de créer le *cmd_arg[] pour execve

char	*create_full_path(char *path, char *cmd)
{
	char	*result;
	char	*temp;

	temp = ft_strjoin(path, "/");
	if (!temp)
		exit(EXIT_FAILURE);
	result = ft_strjoin(temp, cmd);
	if (!result)
		exit(EXIT_FAILURE);
	return (result);
}

void	handle_first_cmd(char **av, char *path, int *pipe_fd, char **env)
{
	int		infile_fd;
	char	**full_command; // par exemple {"ls", "-l"}
	char	*full_path; //par exemple /usr/bin/ls

	infile_fd = open(av[2], O_RDONLY);
	if (-1 == infile_fd)
		open_error();
	if (dup2(infile_fd, 0) == -1) //stdinput redirected to infile
		dup2_error();
	if (dup2(pipe_fd[1], 1) == -1) //stdoutput redirected to write-end pipe
		dup2_error();
	// how to run execve ? i need something that works for all commands
}

int main(int ac, char *av[], char *env[])
{
	int		pid;
	int		pipe_fd[2];
    char	*path1;
	char	*path2;

	parsing(ac, av, env);
	path1 = find_path_command(av[2], env);
	path2 = find_path_command(av[3], env);
	if (NULL == path1 || NULL == path2)
		error_exit();
	if (pipe(pipe_fd) == -1)
		return (free_paths(path1, path2), write(1, "error pipe\n", 11), 1);
	pid = fork();
	if (-1 == pid)
		return (free_paths(path1, path2), write(1, "error fork\n", 11), 1);
	//if (1 == pid)
		//handle_first_cmd
	//else
		//handle_sec_cmd
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