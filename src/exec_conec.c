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

static void	first_kill(t_words *word, int *p, char **env)
{
//	ft_dprintf(2, "in -> %d\n", word->in);
	if (dup2(word->in, STD_IN) == -1)
		exit(1);
	close(p[0]);
	if (dup2(p[1], STD_OUT) == -1)
		exit(1);
	close(p[1]);
	execve(word->path, word->cmd, env);
	exit(after_exec(word));
}

static void	last_kill(t_words *word, int *p, char **env)
{
//	ft_dprintf(2, "out -> %d\n", word->out);
	if (word->out != STD_OUT && word->out > 1)
	{
		if (dup2(word->out, STD_OUT) == -1)
			exit(1);
		close(word->out);
	}
	close(p[1]);
	if (dup2(p[0], STD_IN) == -1)
		exit(1);
	close(p[0]);
	execve(word->path, word->cmd, env);
	exit(after_exec(word));
}

static void	kill_child(t_shell *sh, int *p, char **env, int process)
{
	//pid_t	pid;
	int which;

	which = sh->pipes;
	if (process == which)
	{
	//	pid = fork();
	//	if (pid == -1)
	//		exit(1);
	//	if (pid == 0)
	//		kill_child(sh, p, env, --process);
	//	else
			first_kill(sh->words, p, env);
	}
	else if (process == 0)
	{
		last_kill(sh->words, p, env);
	}
	else
	{
		if (dup2(p[1], STD_IN) == -1)
			exit(1);
		close(p[1]);
		if (dup2(p[0], STD_OUT) == -1)
			exit(1);
		close(p[0]);
		execve(sh->words->path, sh->words->cmd, env);
		exit(after_exec(sh->words));
	}	
}

static void	child_process(t_shell *sh, int *fds, char **env, int process, int *p)
{
	fds = process_redir(sh->redir, fds);
	if (fds[0] == -1 || fds[1] == -1)
		exit(EXIT_FAILURE);
	else if (sh->words && (fds[0] == 0 || fds[1] == 1))
	{
		sh->words->in = fds[0];
		sh->words->out = fds[1];
	}
	if (char_is_inside(sh->words->cmd[0], '/') < 0)
		find_path(sh->words);
	else
		sh->words->path = ft_strdup(sh->words->cmd[0]);
	kill_child(sh, p, env, process);
}

int process_connector(t_shell *sh, int process, char **env, int *fds)
{
	pid_t	pid;
	int	wstatus;
	int	p[2];
	t_words *w;
	t_redir *re;

	w = sh->words;
	re = sh->redir;
	if (pipe(p))
		exit(1);
	while (process >= 0)
	{
		pid = fork();
		if (pid == -1)
			exit(1);
		if (pid == 0)
		{
			sh->words = w;
			sh->redir = re;	
			child_process(sh, fds, env, process, p);
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
