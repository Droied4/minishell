/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deordone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:38:35 by deordone          #+#    #+#             */
/*   Updated: 2024/06/12 18:48:23 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_case(t_shell *sh, t_redir *redir, int last_in)
{
	char	*doc;

	int		len;
	int		p[2];
	int		fd;
	
	(void)sh;
	if (last_in != 0)
		close(last_in);
	fd = dup(0);
	ft_signals(HEREDOC);
	if (pipe(p) < 0)
		exit(1);
	while (42)
	{
		doc = readline("> ");
		if (doc == NULL || g_signals != 0)
		{
			dup2(fd, 0);
			break ;
		}
		last_in = p[0];
		if (ft_strlen(doc) > ft_strlen(redir->file))
			len = ft_strlen(doc);
		else
			len = ft_strlen(redir->file);
		if (!doc || !redir->file || ft_strncmp(doc, redir->file, len) == 0)
			break ;
		doc = expand_string(sh, doc);
		ft_putstr_fd(doc, p[1]);
		ft_putstr_fd("\n", p[1]);
		free(doc);
	}
	close(p[1]);
	close(fd);
	ft_putstr_fd("\n\0", p[1]);
	free(doc);
	return (last_in);
}


