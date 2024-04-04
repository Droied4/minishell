/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deordone <deordone@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 05:40:25 by deordone          #+#    #+#             */
/*   Updated: 2024/04/04 14:03:03 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

//hacer funcion simple cmd 
static int smpl_cmd(t_redir *redir, t_words *word, int *fds, char **env)
{
	if (redir)
		fds = process_redir(redir, fds);
	if (fds[0] == -1 || fds[1] == -1)
		return (EXIT_FAILURE);
	if (word)
		return (process_word(word, fds, env));
	return (EXIT_SUCCESS);
}

static void process_pipes(t_shell *sh, int pipes, int *fds)
{
	int pipe_fd[2];
	int max = stock_of(sh, PIPE);

	if (pipe(pipe_fd) < 0)
		exit(1);
	if (fds[0] == 0 && pipes != max)
	{
		close(pipe_fd[1]);
		fds[0] = pipe_fd[0];
	}
	if (fds[1] == 1 && pipes != 0)
	{
		close(pipe_fd[0]);
		fds[1] = pipe_fd[1];
	}
}

static int connector(t_shell *sh, t_redir *redir, t_words *word, int *fds, char **env)
{
	int pipes;
	int *process;
	int i;
	int out;

	i = 0;
	pipes = sh->pipes + 1;
	process = malloc(sizeof(int) * pipes + 1);
	if (!process)
		exit(1);
	while(pipes--)
{
		if (redir)
		{
			fds = process_redir(redir, fds);
			redir = redir->next;
		}
		if (fds[0] == -1 || fds[1] == -1)
			process[i] = EXIT_FAILURE;
		else if (fds[0] == 0 || fds[1] == 1)
				process_pipes(sh, pipes, fds);
		if (word)
		{
			process[i] = process_word(word, fds, env);
			word = word->next;
		}
		i++;
	}
	out = process[i - 1];
	free(process);
	return (out);
}

void	executor(t_shell *sh, char **env)
{
	(void)env;
	t_redir *redir;
	t_words *word;
	int *fds;

	fds = malloc(sizeof(int) * 2);
	if (!fds)
		exit(1);
	redir = sh->redir;
	word = sh->words;
	if (sh->pipes == 0)
		sh->exit_status = smpl_cmd(redir, word, fds, env);
	else
		sh->exit_status = connector(sh, redir, word, fds, env);
	free(fds);
}
