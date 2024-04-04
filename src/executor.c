/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deordone <deordone@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 05:40:25 by deordone          #+#    #+#             */
/*   Updated: 2024/04/04 16:10:56 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

//hacer funcion simple cmd 
static int smpl_cmd(t_shell *sh, int *fds, char **env)
{
	if (sh->redir)
		fds = process_redir(sh->redir, fds);
	if (fds[0] == -1 || fds[1] == -1)
		return (EXIT_FAILURE);
	if (sh->words)
			return (process_word(0, sh->words, fds, env));
	return (EXIT_SUCCESS);
}


static int connector(t_shell *sh, int *fds, char **env)
{
	int pipes;
	t_words *word;
	t_redir *redir;
	int *process;
	int i;
	int out;

	word = sh->words;
	redir = sh->redir;
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
		if (word)
		{
			process[i] = process_word(pipes, word, fds, env);
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
	int *fds;

	fds = malloc(sizeof(int) * 2);
	if (!fds)
		exit(1);
	if (sh->pipes == 0)
		sh->exit_status = smpl_cmd(sh, fds, env);
	else
		sh->exit_status = connector(sh, fds, env);
	free(fds);
}
