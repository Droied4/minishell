/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deordone <deordone@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 16:38:06 by deordone          #+#    #+#             */
/*   Updated: 2024/05/03 02:09:08 by droied           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	after_exec(t_words *word)
{
	if ((errno == EFAULT || errno == EACCES) && (char_is_inside(word->cmd[0],
				'/') < 0))
	{
		ft_dprintf(2, "Error: %s: Command not found\n", word->cmd[0]);
		return (127);
	}
	if (word->cmd)
	{
		open(word->path, O_WRONLY);
		ft_dprintf(2, "Error: %s: %s\n", word->cmd[0], strerror(errno));
	}
	else
		return (0);
	if (errno == ENOENT)
		return (127);
	return (126);
}

void	ft_free_array(char **res)
{
	int	i;

	i = 0;
	if (res)
	{
		while (res[i])
			++i;
		while (--i >= 0)
			free(res[i]);
		free(res);
		res = NULL;
	}
}

void	soft_exit(t_shell *sh)
{
	ft_deltoken(&sh->tokens);
	ft_del_redirs(&sh->pro.r);
	ft_del_words(&sh->pro.w);
	free(sh->line);
}

void	hard_exit(t_shell *sh)
{
	ft_deltoken(&sh->tokens);
	ft_del_redirs(&sh->pro.r);
	ft_del_words(&sh->pro.w);
	clear_history();
	free(sh->line);
	exit(1);
}
