/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_conec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:18:48 by deordone          #+#    #+#             */
/*   Updated: 2024/06/27 11:56:48 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/struct.h"

static void	child_process(t_shell *sh, t_process *pro)
{
	char	**envivar;

	envivar = NULL;
	if (pro->w && pro->w->cmd)
	{
		if (char_is_inside(pro->w->cmd[0], '/') < 0)
		{
			envivar = get_envivar("PATH=", sh->matriz_env);
			pro->w->path = ft_check_path(envivar, pro->w->cmd);
		}
		else
			pro->w->path = ft_strdup(pro->w->cmd[0]);
		free_matrix(&envivar);
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
	if (pro->w->out != pro->p[1])
		close(pro->p[1]);
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

static void	fork_child(t_shell *sh, t_process *pro)
{
	pro->pid = fork();
	if (pro->pid == -1)
		exit(1);
	if (pro->pid == 0)
	{
		if (pro->p[0] != pro->w->in)
			close(pro->p[0]);
		child_process(sh, pro);
	}
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
		if (pro.w->in == -2)
			return (130);
		fork_child(sh, &pro);
		after_fork(&pro);
	}
	close(pro.p[0]);
	while (pro.pid > 0)
		pro.pid = waitpid(-1, &pro.wstatus, 0);
	if (WIFEXITED(pro.wstatus))
		return (WEXITSTATUS(pro.wstatus));
	return (0);
}
