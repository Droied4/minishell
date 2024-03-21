/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deordone <deordone@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:55:14 by deordone          #+#    #+#             */
/*   Updated: 2024/03/21 13:16:38 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.c"

static int child_process(t_block *block)
{
	if (block->in != STDIN)
		printf("hacer redireccion de la entrada");
	if (block->out == STDOUT)	
		printf("hacer redireccion de la salida");
	execve(path, cmd, env);
}

void	execute_cmd(block)
{
	pid_t pid;

	pid = fork();
	if (!fork)
		exit (1);
	if (pid == 0)
	{
		child_process(block);
	}
	else
	{
		//esperar al hijo
	}
}

void	execution(t_shell *sh, char **env)
{
	t_block *block;

	block = sh->block;
	while (block)
	{
		//if (block->type == B_PIPE)	
		//if (block->type == B_REDIR)	
		//if (block->type == B_BUILT)	
		//if (block->type == B_SQUOTES)	
		//if (block->type == B_DQUOTES)	
		if (block->type == B_CMD)	
			execute_cmd(block);
		//if (block->type == B_FILE)	
		block = block->next;
	}	
}
