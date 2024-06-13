/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 05:40:25 by deordone          #+#    #+#             */
/*   Updated: 2024/06/13 15:43:17 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	kill_child(t_shell *sh, t_process *pro)
{
	if (pro->w->in != STD_IN)
	{
		if (dup2(pro->w->in, STD_IN) == -1)
			exit(1);
		close(pro->w->in);
	}
	else
		close(pro->p[0]);
	if (pro->w->out != STD_OUT)
	{
		if (dup2(pro->w->out, STD_OUT) == -1)
			exit(1);
		close(pro->w->out);
	}
	else
		close(pro->p[1]);
	if (pro->w->cmd)
	{
		if (is_builtin(pro->w->cmd[0]) > 0)
			exit(execute_builtins(sh, sh->matriz_env));
		execve(pro->w->path, pro->w->cmd, sh->matriz_env);
	}
	exit(after_exec(pro->w));
}

static int	do_builtin(t_shell *sh)
{
	int		status;
	t_words	*word;

	status = 0;
	word = sh->pro.w;
	if (word->in != STD_IN)
	{
		if (dup2(word->in, STD_IN) == -1)
			exit(EXIT_FAILURE);
		close(word->in);
	}
	if (word->out != STD_OUT)
	{
		if (dup2(word->out, STD_OUT) == -1)
			exit(EXIT_FAILURE);
		close(word->out);
	}
	status = execute_builtins(sh, sh->matriz_env);
	if (dup2(0, STD_IN) == -1)
		exit(EXIT_FAILURE);
	if (dup2(1, STD_OUT) == -1)
		exit(EXIT_FAILURE);
	return (status);
}

static int	smpl_cmd(t_shell *sh)
{
	if (sh->pro.r)
		process_redir(sh, &sh->pro);
	if (sh->pro.w->in == -2)
		return (130);
	if (sh->pro.w)
	{
		if (sh->pro.w->in == -1 || sh->pro.w->out == -1)
			return (EXIT_FAILURE);
		if (sh->pro.w->cmd)
		{
			if (is_builtin(sh->pro.w->cmd[0]) > 0)
				return (do_builtin(sh));
			return (process_word(sh, 0, 0));
		}
	}
	return (EXIT_SUCCESS);
}

static int	connector(t_shell *sh)
{
	int	process;
	int	final;

	final = EXIT_SUCCESS;
	process = -1;
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
