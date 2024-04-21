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
	//(void)p;
	if (sh->words->in != STD_IN)
	{
		//ft_dprintf(2, "2in -> %d\n", sh->words->in);
		if (dup2(sh->words->in, STD_IN) == -1)
			exit(1);
		close(sh->words->in);
	}
	else
		close(p[0]);
	if (sh->words->out != STD_OUT)
	{
		//ft_dprintf(2, "2out -> %d\n", sh->words->out);
		if (dup2(sh->words->out, STD_OUT) == -1)
			exit(1);
		close(sh->words->out);
	}
	else
		close(p[1]);
	execve(sh->words->path, sh->words->cmd, env);
	exit(after_exec(sh->words));
}

int esperanding(pid_t pid)
{
	int zombie_status;
	pid_t zombie_pid;
	int status;
	pid_t got_pid;
	got_pid = waitpid(-1, &status, 0);
	while (got_pid != pid)
	{
		if (got_pid < 0 && errno == ECHILD)
		{
			status = 0;
			break;
		}
		got_pid = waitpid (-1, &status, 0);
	}
		zombie_pid = waitpid(-1, &zombie_status, WNOHANG);
	while (zombie_pid > 0)
	{
		zombie_pid = waitpid(-1, &zombie_status, WNOHANG);
	}
	if (WIFSIGNALED (status))
		return (128 + WTERMSIG (status));
	else
		return (WEXITSTATUS (status));
}


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
	int	martuta[2];
	int	wstatus;
	int i;
	int	santito[2];
	int	p[2];
	t_words *w;
	t_redir *re;
	
	i = 0;
	w = sh->words;
	re = sh->redir;
	santito[0] = 0;
	while (process >= 0)
	{
		if (process >= 1)
		{
			if (pipe(p) < 0)
				exit(EXIT_FAILURE);
			santito[1] = p[1];
		}
		else
		{
			santito[1] = 1;
		}
		pid = fork();
		if (pid == -1)
			exit(1);
		if (pid == 0)
		{
			w->in = santito[0];
			w->out = santito[1];
			sh->words = w;
			sh->redir = re;	
			child_process(sh, fds, env, process, p);
		}
		martuta[i] = pid;
		i++;
		if (santito[0] != 0)
			close(santito[0]);
		if (santito[1] != 1)
			close(santito[1]);
		santito[0] = p[0];
	//	while (re && re->type != PIPE)
	//		//re = re->next;
		w = w->next;			
		process--;
	}
	close(p[0]);
	i = -1;
	//while (martuta[++i] < sh->pipes)
		waitpid (martuta[1], &wstatus, 0);
		waitpid (martuta[0], &wstatus, WUNTRACED);
	//return (esperanding(pid));
	if (WIFEXITED(wstatus))
		return (WEXITSTATUS(wstatus));
	return (0);
}
