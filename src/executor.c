/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deordone <deordone@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 05:40:25 by deordone          #+#    #+#             */
/*   Updated: 2024/05/03 01:30:38 by droied           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

static int do_builtin(t_shell *sh)
{
	t_words *word;

	word = sh->words;
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
	execute_builtins(sh, sh->matriz_env);
	if (dup2(0, STD_IN) == -1)
		exit(1);
	if (dup2(1, STD_OUT) == -1)
		exit(1);
	return (0);
}

static int smpl_cmd(t_shell *sh)
{
    if (sh->redir)
		process_redir(sh->pro);
	if (sh->words)
	{
		if (sh->words->in == -1 || sh->words->out == -1)
			return (EXIT_FAILURE);
		if (sh->words->cmd)
		{
			if (is_builtin(sh->words->cmd[0]) > 0)
					return (do_builtin(sh));
			return (process_word(sh));
		}
	}
	return (EXIT_SUCCESS);
}

static int connector(t_shell *sh)
{
	int process;
	int final;
	
	final = EXIT_SUCCESS;
	process = sh->pipes;
	final = process_connector(sh, process);
	return (final);
}

void	executor(t_shell *sh)
{

	if (sh->pipes == 0)
		sh->exit_status = smpl_cmd(sh);
	else
		sh->exit_status = connector(sh);
}
