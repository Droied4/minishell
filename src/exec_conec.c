/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_conec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deordone <deordone@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:18:48 by deordone          #+#    #+#             */
/*   Updated: 2024/04/09 17:23:15 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	kill_child(t_process *pro, char **env)
{
	if (pro->in != STD_IN)
	{
	//	ft_dprintf(2, "2in -> %d\n", pro->in);
		if (dup2(pro->in, STD_IN) == -1)
			exit(1);
		close(pro->in);
	}
	else
		close(pro->p[0]);
	if (pro->out != STD_OUT)
	{
	//	ft_dprintf(2, "2out -> %d\n", pro->out);
		if (dup2(pro->out, STD_OUT) == -1)
			exit(1);
		close(pro->out);
	}
	else
		close(pro->p[1]);
	execve(pro->words->path, pro->words->cmd, env);
	exit(after_exec(pro->words));
}

static void	child_process(t_process *pro, char **env)
{
	if (char_is_inside(pro->words->cmd[0], '/') < 0)
		find_path(pro->words);
	else
		pro->words->path = ft_strdup(pro->words->cmd[0]);
	kill_child(pro, env);
}

static void before_fork(int process, t_process *pro, t_shell *sh)
{
	if (process < sh->pipes)
	{
		if (pipe(pro->p) < 0)
			exit(EXIT_FAILURE);
		pro->out = pro->p[1];
	}
	else
		pro->out = 1;
	//hacer redirecciones
}

static void after_fork(t_process *pro)
{
	if (pro->in != 0)
		close(pro->in);
	if (pro->out != 1)
		close(pro->out);
	else
		close(pro->p[1]);
	pro->in = pro->p[0];
	while (pro->redir && pro->redir->type != PIPE)
		pro->redir = pro->redir->next;
	pro->words = pro->words->next;			
}

int process_connector(t_shell *sh, int process, char **env, int *fds)
{
	(void)fds;
	t_process pro;
	
	pro.in = 0;
	pro.words = sh->words;
	pro.redir = sh->redir;
	pro.pid = malloc(sizeof(pid_t) * (sh->pipes + 1));
	if (!pro.pid)
		exit(1);
	process = -1;
	while (++process <= sh->pipes)
	{
		before_fork(process, &pro, sh);
		pro.pid[process] = fork();
		if (pro.pid[process] == -1)
			exit(1);
		if (pro.pid[process] == 0)
			child_process(&pro, env);
		after_fork(&pro);
	}
	close(pro.p[0]);
	while (--process >= 0)
		waitpid (pro.pid[process], &pro.wstatus, 0);
	free(pro.pid);
	if (WIFEXITED(pro.wstatus))
		return (WEXITSTATUS(pro.wstatus));
	return (0);
}
