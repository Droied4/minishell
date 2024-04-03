/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deordone <deordone@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 05:40:25 by deordone          #+#    #+#             */
/*   Updated: 2024/04/03 15:31:27 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

//hacer funcion simple cmd 
static int smpl_cmd(t_redir *redir, t_words *word, int *fds, char **env)
{
	if (redir)
		fds = process_redir(redir, fds);
	if (fds[0] == -1 || fds[1] == -1)
		return (EXIT_FAILURE);
	if (word)
		return (process_word(word, fds, env));
	return (0);
}

//hacer funcion connector cmd
static int connector(t_redir *redir, t_words *word, int *fds)
{
	(void)redir;
	(void)word;
	(void)fds;
	printf("connector");
	return (0);
}

void	executor(t_shell *sh, char **env)
{
	(void)env;
	t_redir *redir;
	t_words *word;
	int *fds;

	fds = malloc(sizeof(int) * 2);
	if (!fds)
		exit(1);
	redir = sh->redir;
	word = sh->words;
	if (sh->pipes == 0)
		sh->exit_status = smpl_cmd(redir, word, fds, env);
	else
		connector(redir, word, fds);
	free(fds);
}
