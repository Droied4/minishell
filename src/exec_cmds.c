/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deordone <deordone@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 05:30:41 by deordone          #+#    #+#             */
/*   Updated: 2024/05/03 02:20:36 by droied           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void child_process(t_shell *sh)
{
	t_words *word;

	word = sh->pro.w;
	if (word->in != STD_IN)
	{
		if (dup2(word->in, STD_IN) == -1)
			exit(1);
		close(word->in);
	}
	if (word->out != STD_OUT)
	{
		if (dup2(word->out, STD_OUT) == -1)
			exit(1);
		close(word->out);
	}
	execve(word->path, word->cmd, sh->matriz_env);
	exit(after_exec(word));
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

void find_path(t_words *word)
{
	char **paths;
	char *path;
	
	path = getenv("PATH");
	paths = ft_split(path, ':');
	word->path = ft_check_path(paths, word->cmd);
	ft_free_array(paths);
}

int process_word(t_shell *sh)
{
	pid_t pid;
	int wstatus;
	t_words *word;
	int exit_status;
	
	word = sh->pro.w;	
	if (char_is_inside(word->cmd[0], '/') < 0)
		find_path(word);
	else
		word->path = ft_strdup(word->cmd[0]);
	exit_status = 0;
	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid > 0)
		waitpid(0, &wstatus, 0);
	else
		child_process(sh);
	if (word->in != STD_IN)
		close(word->in);
	if (word->out != STD_OUT)
		close(word->out);
	if (WIFEXITED(wstatus))
		exit_status = WEXITSTATUS(wstatus);
	return (exit_status);
}
