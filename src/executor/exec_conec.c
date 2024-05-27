/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_conec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:18:48 by deordone          #+#    #+#             */
/*   Updated: 2024/05/27 22:08:52 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "struct.h"

static void	kill_child(t_shell *sh, t_process *pro)
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
		{
			execute_builtins(sh, sh->matriz_env);
			exit(0);
		}
		execve(pro->w->path, pro->w->cmd, sh->matriz_env);
	}
	exit(after_exec(pro->w));
}

static void	child_process(t_shell *sh, t_process *pro)
{
	if (pro->w && pro->w->cmd)
	{
		if (char_is_inside(pro->w->cmd[0], '/') < 0)
			pro->w->path = ft_check_path(get_envivar("PATH=", sh->matriz_env), pro->w->cmd);
		else
			pro->w->path = ft_strdup(pro->w->cmd[0]);
	}
	kill_child(sh, pro);
}

static void	before_fork(int process, t_process *pro, t_shell *sh)
{
	if (process <= sh->pipes)
	{
		pro->w->in = pro->p[0];
		if (pipe(pro->p) < 0)
			exit(EXIT_FAILURE);
		pro->w->out = pro->p[1];
	}
	if (process == sh->pipes)
		pro->w->out = 1;
	process_redir(sh, pro);
	if (pro->w->next)
	{
		pro->w->next->in = pro->w->in;
		pro->w->next->out = pro->w->out;
	}
}

static void	after_fork(t_process *pro)
{
	if (pro->w->in != STD_IN)
		close(pro->w->in);
	if (pro->w->out != STD_OUT)
		close(pro->w->out);
	else
		close(pro->p[1]);
	while (pro->r && pro->r->type != PIPE)
		pro->r = pro->r->next;
	if (pro->r)
		pro->r = pro->r->next;
	pro->w = pro->w->next;
}

int	process_connector(t_shell *sh, int process)
{
	t_process	pro;

	pro.w = sh->pro.w;
	pro.r = sh->pro.r;
	pro.p[0] = 0;
	process = -1;
	while (++process <= sh->pipes)
	{
		before_fork(process, &pro, sh);
		pro.pid = fork();
		if (pro.pid == -1)
			exit(1);
		if (pro.pid == 0)
		{
			if (pro.p[0] != pro.w->in)
				close(pro.p[0]);
			child_process(sh, &pro);
		}
		after_fork(&pro);
	}
	close(pro.p[0]);
	while (pro.pid > 0)
		pro.pid = waitpid(-1, &pro.wstatus, 0);
	if (WIFEXITED(pro.wstatus))
		return (WEXITSTATUS(pro.wstatus));
	return (0);
}
