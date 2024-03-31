/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deordone <deordone@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 05:14:03 by deordone          #+#    #+#             */
/*   Updated: 2024/03/31 05:16:00 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int less_case(t_redir *redir, int last_in)
{
		if (last_in != 0)
			close(last_in);
		last_in = open(redir->file, O_RDONLY);
		if (last_in == -1)
		{
			printf("Error: %s: %s\n", redir->file, strerror(errno));
			exit(EXIT_FAILURE);
		}
		return (last_in);
}

/*static int heredoc_case(t_redir *redir, int last_in)
{

}
*/
static int great_case(t_redir *redir, int last_out)
{		
		if (last_out != 0)
			close(last_out);
		last_out = open(redir->file, O_TRUNC | O_CREAT | O_RDWR, 0666);
		if (last_out == -1)
		{
			printf("Error: %s: %s\n", redir->file, strerror(errno));
			exit(EXIT_FAILURE);
		}
		return (last_out);
}

static int append_case(t_redir *redir, int last_out)
{
		if (last_out != 0)
			close(last_out);
		last_out = open(redir->file, O_APPEND | O_CREAT | O_RDWR, 0666);
		if (last_out == -1)
		{
			printf("Error: %s: %s\n", redir->file, strerror(errno));
			exit(EXIT_FAILURE);
		}
		return (last_out);
}

void threat_redir(t_redir *redir)
{
	int last_in;
	int last_out;

	last_in = 0;
	last_out = 0;
	while (redir)
	{
		if (redir->type == LESS)
			last_in = less_case(redir, last_in);
		//else if (redir->type == DLESS)
		//	last_in = heredoc_case(redir, last_in);
		else if (redir->type == GREAT)
			last_out = great_case(redir, last_out);
		else if (redir->type == DGREAT)
			last_out = append_case(redir, last_out);
		redir = redir->next;
	}
}



