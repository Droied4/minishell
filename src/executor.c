/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deordone <deordone@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 05:40:25 by deordone          #+#    #+#             */
/*   Updated: 2024/04/03 14:00:04 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

//hacer funcion simple cmd 
//static int smpl_cmd();

//hacer funcion connector cmd
//static int connector();

void	executor(t_shell *sh, char **env)
{
	(void)env;
	t_redir *redir;
	t_words *word;
	int *fds;

	fds = malloc(sizeof(int) * 2);
	if (!fds)
		exit(-1);
	redir = sh->redir;
	word = sh->words;
//	Estructura smpl cmd
		if (redir)
			fds = process_redir(redir, fds);
		if (fds[0] == -1 || fds[1] == -1)
		{
			sh->exit_status = EXIT_FAILURE;
			free(fds);
			return ;
		}
		if (word)
			sh->exit_status = process_word(word, fds, env);
		free(fds);
}
