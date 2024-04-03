/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deordone <deordone@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 05:30:41 by deordone          #+#    #+#             */
/*   Updated: 2024/04/03 15:14:46 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
static void child_process(t_words *word, char **env)
{
	if (word->in != STD_IN && word->in > 0)
	{
		if (dup2(word->in, STD_IN) == -1)
			exit(1);
	}
	if (word->out != STD_OUT && word->out > 1)
	{
		if (dup2(word->out, STD_OUT) == -1)
			exit(1);
		close(word->out);
	}
	if (execve(word->path, word->cmd, env) < 0)
	{
		printf("Error: %s: %s\n", word->cmd[0], strerror(errno));
		if (access(word->path, F_OK) == -1)
			exit(127);
		else
			exit(126);//esto hay que cambiarlo
	}
}

static char	*ft_aux_check(char *new_path, char *new_cmd)
{
	if (access(new_cmd, F_OK | X_OK) == 0)
		return (new_cmd);
	else if (access(new_cmd, X_OK) == -1)
	{
		free(new_path);
		free(new_cmd);
		return (NULL);
	}
	else
	{
		free(new_path);
		free(new_cmd);
	}
	return (NULL);
}

static char	*ft_check_path(char **paths, char **cmd)
{
	int		i;
	int		j;
	char	*new_cmd;
	char	*new_path;

	i = 0;
	j = 0;
	if (access(cmd[0], X_OK) == 0)
		return (ft_strdup(cmd[0]));
	while (paths[i] != NULL)
		i++;
	while (i > j)
	{
		new_path = ft_strjoin(paths[j], "/");
		new_cmd = ft_strjoin(new_path, cmd[0]);
		new_cmd = ft_aux_check(new_path, new_cmd);
		if (new_cmd)
		{
			free(new_path);
			return (new_cmd);
		}
		j++;
	}
	return (NULL);
}

static void find_path(t_words *word)
{
	char **paths;
	char *path;
	
	path = getenv("PATH");
	paths = ft_split(path, ':');
	word->path = ft_check_path(paths, word->cmd);
	ft_free_array(paths);
}

int process_word(t_words *word, int *fds, char **env)
{
	pid_t pid;
	int parent_aux;
	int exit_status;

	exit_status = 0;
	find_path(word);
	word->in = fds[0];
	word->out = fds[1];
	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid > 0)
		waitpid(0, &parent_aux, 0);
	else
		child_process(word, env);
	if (WIFEXITED(parent_aux))
		exit_status = WEXITSTATUS(parent_aux);
	return (exit_status);
}
