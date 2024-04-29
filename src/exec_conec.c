/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_conec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deordone <deordone@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:18:48 by deordone          #+#    #+#             */
/*   Updated: 2024/04/29 17:53:11 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	kill_child(t_process *pro, t_shell *sh)
{
	if (pro->in != STD_IN)
	{
		if (dup2(pro->in, STD_IN) == -1)
		{
			BUG;
			exit(1);
		}
		close(pro->in);
	}
	else
		close(pro->p[0]);
	if (pro->out != STD_OUT)
	{
		if (dup2(pro->out, STD_OUT) == -1)
			exit(1);
		close(pro->out);
	}
	else
		close(pro->p[1]);
	if (pro->words->cmd)
	{
		if (is_builtin(pro->words->cmd[0]) > 0)
		{
			execute_builtins(sh, sh->matriz_env);
			exit(0);
		}
		execve(pro->words->path, pro->words->cmd, sh->matriz_env);
	}
	exit(after_exec(pro->words));
}

static void	child_process(t_process *pro, t_shell *sh)
{
	if (pro->words && pro->words->cmd)
	{
		if (char_is_inside(pro->words->cmd[0], '/') < 0)
			find_path(pro->words);
		else
			pro->words->path = ft_strdup(pro->words->cmd[0]);
	}
	kill_child(pro, sh);
}

static void	before_fork(int process, t_process *pro, t_shell *sh)
{
	t_shell sh1;
	
	sh1 = *sh;
	sh1.redir = pro->redir;
	if (process <= sh->pipes)
	{
		pro->in = pro->p[0];
		if (pipe(pro->p) < 0)
			exit(EXIT_FAILURE);
		pro->out = pro->p[1];
	}
	if (process == 0)
		pro->in = 0;
	else if (process == sh->pipes)
		pro->out = 1;
	process_redir(&sh1);
	if (sh->words->in > 0)
	{
		close(pro->p[0]);
		pro->in = sh->words->in;
	}
	if (sh->words->out > 1)
	{
		close(pro->p[1]);
		pro->out = sh->words->out;
	}
	if (sh->words->next)
	{
		sh->words->next->in = sh->words->in;
		sh->words->next->out = sh->words->out;
	}
}

static void	after_fork(t_process *pro)
{
	if (pro->in != STD_IN)
		close(pro->in);
	if (pro->out != STD_OUT)
		close(pro->out);
	else
		close(pro->p[1]);
	while (pro->redir && pro->redir->type != PIPE)
		pro->redir = pro->redir->next;
	if (pro->redir)
		pro->redir = pro->redir->next;
	pro->words = pro->words->next;
}

int	process_connector(t_shell *sh, int process)
{
	t_process	pro;
	pid_t		pid;

	pro.in = 0;
	pro.words = sh->words;
	pro.redir = sh->redir;
	process = -1;
	while (++process <= sh->pipes)
	{
		before_fork(process, &pro, sh);
		pid = fork();
		if (pid == -1)
			exit(1);
		if (pid == 0)
		{
		//	if (process > 0) hace que funcione el cat | ls
		//		close(pro.p[0]);
			child_process(&pro, sh);
		}
		after_fork(&pro);
	}
	close(pro.p[0]);
	while (pid > 0)
		pid = waitpid(-1, &pro.wstatus, 0);
	if (WIFEXITED(pro.wstatus))
		return (WEXITSTATUS(pro.wstatus));
	return (0);
}
