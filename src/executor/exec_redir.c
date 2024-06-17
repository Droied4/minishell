/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 05:14:03 by deordone          #+#    #+#             */
/*   Updated: 2024/06/17 15:29:37 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	less_case(t_redir *redir, int last_in)
{
	if (last_in != 0)
		close(last_in);
	last_in = open(redir->file, O_RDONLY);
	if (last_in == -1)
	{
		printf("Error: %s: %s\n", strerror(errno), redir->file);
		return (-1);
	}
	return (last_in);
}

static int	great_case(t_redir *redir, int last_out)
{
	if (last_out != 1)
		close(last_out);
	last_out = open(redir->file, O_TRUNC | O_CREAT | O_RDWR, 0666);
	if (last_out == -1)
	{
		printf("Error: %s: %s\n", strerror(errno), redir->file);
		return (-1);
	}
	return (last_out);
}

static int	append_case(t_redir *redir, int last_out)
{
	if (last_out != 1)
		close(last_out);
	last_out = open(redir->file, O_APPEND | O_CREAT | O_RDWR, 0666);
	if (last_out == -1)
	{
		printf("Error: %s: %s\n", strerror(errno), redir->file);
		return (-1);
	}
	return (last_out);
}

void	process_redir(t_shell *sh, t_process *pro)
{
	int		last_in;
	int		last_out;
	t_redir	*redir;

	(void)sh;
	last_in = 0;
	last_out = 1;
	redir = pro->r;
	while (redir && redir->type != PIPE)
	{
		if (redir->type == LESS && last_in > -1 && last_out != -1)
			last_in = less_case(redir, last_in);
		else if (redir->type == DLESS && last_in > -1)
			last_in = heredoc_case(sh, redir, last_in, 0);
		else if (redir->type == GREAT && last_in != -1 && last_out != -1)
			last_out = great_case(redir, last_out);
		else if (redir->type == DGREAT && last_in != -1 && last_out != -1)
			last_out = append_case(redir, last_out);
		redir = redir->next;
	}
	if (last_in > 0 || last_in < 0)
		pro->w->in = last_in;
	if (last_out > 1 || last_out == -1)
		pro->w->out = last_out;
}
