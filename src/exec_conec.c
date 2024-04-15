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

static void	kill_child(t_shell *sh, char **env, int *p)
{
	(void)p;
//	ft_dprintf(2, "2in -> %d\n", sh->words->in);
	if (dup2(sh->words->in, STD_IN) == -1)
		exit(1);
	if (sh->words->in > 0)
		close(sh->words->in);
//	ft_dprintf(2, "2out -> %d\n", sh->words->out);
	if (dup2(sh->words->out, STD_OUT) == -1)
		exit(1);
	if (sh->words->out > 1)
		close(sh->words->out);
	ft_dprintf(2, "\n");;
	execve(sh->words->path, sh->words->cmd, env);
	exit(after_exec(sh->words));
}
/*
static void	redir_pipes(t_shell *sh, int *p, int process)
{
	(void)process;
//	if ((process % 2) == 0)
//	{
//		sh->words->in = p[0];
//		sh->words->out = p[1];
//	}
//	else 
//	{
		sh->words->in = p[1];
		sh->words->out = p[0];
//	}
}*/

static void	child_process(t_shell *sh, int *fds, char **env, int process, int *p)
{
	(void)fds;
	(void)process;
/*	fds = process_redir(sh->redir, fds);
	if (fds[0] == -1 || fds[1] == -1)
		exit(EXIT_FAILURE);
	else if (sh->words && (fds[0] == STD_IN || fds[1] == STD_OUT))
		redir_pipes(sh, p, process);	*/
	if (char_is_inside(sh->words->cmd[0], '/') < 0)
		find_path(sh->words);
	else
		sh->words->path = ft_strdup(sh->words->cmd[0]);
	kill_child(sh, env, p);
}

int process_connector(t_shell *sh, int process, char **env, int *fds)
{
	pid_t	pid;
	int	wstatus;
	int	p[2];
	t_words *w;
	t_redir *re;

	int which_pipe;

	which_pipe = sh->pipes;
	w = sh->words;
	re = sh->redir;
	while (process >= 0)
	{
		if ((process % 2) != 0)
		{
			pipe(p);
		}
		fds = process_redir(re, fds);
		if (fds[0] == -1 || fds[1] == -1)
			exit(EXIT_FAILURE);
		//else if (sh->words && (fds[0] == STD_IN || fds[1] == STD_OUT))
		//	//redir_pipes(sh, p, process);
			w->in = p[0];
			w->out = p[1];
		if (process == 0)
		{
			close(w->out);
			w->out = 1;
		}
		else if (process == which_pipe)
		{
			w->in = 0;
		}
		pid = fork();
		if (pid == -1)
			exit(1);
		if (pid == 0)
		{
			sh->words = w;
			sh->redir = re;	
			child_process(sh, fds, env, process, p);
		}	
		if (process == 0)
		{
			close(p[0]);
		}

		while (re && re->type != PIPE)
			re = re->next;
		w = w->next;
		process--;
	}
	waitpid(-1, &wstatus, 0);
	if (WIFEXITED(wstatus))
		return (WEXITSTATUS(wstatus));
	return (0);
}
