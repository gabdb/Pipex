/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 16:19:45 by gnyssens          #+#    #+#             */
/*   Updated: 2024/08/13 22:46:18 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int ac, char *av[], char *env[])
{
    int i;

    i = 0;
    while(env[i] != NULL)
    {
        if (env[i][0] == 'P')
            printf("%s\n", env[i]);
        i++;
    }
    return 0;
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