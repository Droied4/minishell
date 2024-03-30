/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deordone <deordone@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 17:33:30 by deordone          #+#    #+#             */
/*   Updated: 2024/03/27 15:52:49 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
static void child_process(t_block *block)
{
	if (block->in != STD_IN)
	{
		printf("hacer redireccion de la entrada\n");
	}
	if (block->out != STD_OUT)
	{
		printf("hacer redireccion de la salida\n");
	}
	if (execve(block->path, block->cmd, NULL) < 0)
		printf("cagaste\n");
}

static char	*ft_aux_check(char *new_path, char *new_cmd)
{
	if (access(new_cmd, F_OK | X_OK) == 0)
		return (new_cmd);
	else if (access(new_cmd, X_OK) == -1)
	{
		free(new_path);
		free(new_cmd);
		return (NULL);
	}
	else
	{
		free(new_path);
		free(new_cmd);
	}
	return (NULL);
}

static char	*ft_check_path(char **paths, char **cmd)
{
	int		i;
	int		j;
	char	*new_cmd;
	char	*new_path;

	i = 0;
	j = 0;
	if (access(cmd[0], X_OK) == 0)
		return (ft_strdup(cmd[0]));
	while (paths[i] != NULL)
		i++;
	while (i > j)
	{
		new_path = ft_strjoin(paths[j], "/");
		new_cmd = ft_strjoin(new_path, cmd[0]);
		new_cmd = ft_aux_check(new_path, new_cmd);
		if (new_cmd)
		{
			free(new_path);
			return (new_cmd);
		}
		j++;
	}
	return (NULL);
}

static char **find_path(t_block *block)
{
	char **paths;
	char *path;
	
	path = getenv("PATH");
	paths = ft_split(path, ':');
	block->path = ft_check_path(paths, block->cmd);
	print_blocks(block);
	return (paths);
}

void	execute_cmd(t_block *block)
{
	pid_t pid;
	int parent_aux;

	find_path(block);

	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid > 0)
		waitpid(0, &parent_aux, 0);
	else
		child_process(block);
}


void	executor(t_shell *sh, char **env)
{
	t_block *block;
	(void)env;

	block = sh->block;
	while (block)
	{
		//if (block->type == B_PIPE)	
//		if (block->type == B_REDIR)
		//if (block->type == B_BUILT)	
		//if (block->type == B_SQUOTES)	
		//if (block->type == B_DQUOTES)	
		if (block->type == B_CMD)	
			execute_cmd(block);
		//if (block->type == B_FILE)	
		block = block->next;
	}

}*/
