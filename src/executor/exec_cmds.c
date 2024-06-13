/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 05:30:41 by deordone          #+#    #+#             */
/*   Updated: 2024/06/13 20:14:38 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child_process(t_shell *sh)
{
	t_words	*word;

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

char	*ft_check_path(char **paths, char **cmd)
{
	int		i;
	int		j;
	char	*new_cmd;
	char	*new_path;

	i = 0;
	j = 0;
	if (!paths)
		return (NULL);
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
			return (free(new_path), new_cmd);
		j++;
	}
	return (NULL);
}

static int	closing_in_out(t_words *word, int wstatus, int exit_status)
{
	if (word->in != STD_IN)
		close(word->in);
	if (word->out != STD_OUT)
		close(word->out);
	if (WIFEXITED(wstatus))
		exit_status = WEXITSTATUS(wstatus);
	else if (WIFSIGNALED(wstatus))
	{
		if (WTERMSIG(wstatus) == SIGQUIT)
			printf("Quit 3\n");
		exit_status = 128 + WTERMSIG(wstatus);
	}
	return (exit_status);
}

int	process_word(t_shell *sh, int wstatus, int exit_status)
{
	pid_t	pid;
	t_words	*word;
	char	**envivar;

	envivar = NULL;
	word = sh->pro.w;
	ft_signals(NON_INTERACTIVE);
	if (char_is_inside(word->cmd[0], '/') < 0)
	{
		envivar = get_envivar("PATH=", sh->matriz_env);
		word->path = ft_check_path(envivar, word->cmd);
	}
	else
		word->path = ft_strdup(word->cmd[0]);
	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid > 0)
		waitpid(0, &wstatus, 0);
	else
		child_process(sh);
	exit_status = closing_in_out(word, wstatus, exit_status);
	return (free_matrix(&envivar), exit_status);
}
