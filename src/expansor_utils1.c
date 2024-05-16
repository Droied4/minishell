/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 13:12:42 by avolcy            #+#    #+#             */
/*   Updated: 2024/05/16 11:22:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **split_env_var(char *str)
{
    int i;
    int len;
    int position;
    char **splitted;

    len = count_len(str);
    splitted = malloc(sizeof(char *) * (len + 1));
    i = 0;
    while (i < len)
    {
        splitted[i] = find_env_part(str , &position);
        str = &str[position];
        i++;
    }
    splitted[i] = NULL;
    return (splitted);
}
char    *find_env_part(char *str, int *pos)
{
    int i;
    int len;
    char *part;

    len = count_len_env_part(str);
    *pos = len;
    part = malloc(sizeof(char) * (len + 1));
    i = 0;
    while (i < len)
    {
        part[i] = str[i];
        i++;
    }
    part[i] = '\0';
    return (part);
}

char	*is_special_dollar(char *data, int num_dollar, int i)
{
	pid_t	pid;
	char	*print_pid;
	char	*str_pid;

	pid = getpid();
	print_pid = NULL;
	str_pid = ft_itoa(pid);
	while (i++ < num_dollar / 2)
		print_pid = ft_strjoin2(print_pid, str_pid);
	if (num_dollar % 2 == 0)
	{
		if (ft_strlen(data) > (size_t)num_dollar)
		{
			data = data + num_dollar;
			print_pid = ft_strjoin2(print_pid, data);
		}
	}
	else
	{
		data = data + (num_dollar - 1);
		if (!ft_strncmp("$", data, 2))
			print_pid = ft_strjoin2(print_pid, data);
	}
	return (free(str_pid), print_pid);
}

char	*special_cases(char *special, int exit_status)
{
	char	*str_exit_status;

	if (!ft_strncmp("$?", special, 2))
	{
		str_exit_status = ft_itoa(exit_status);
		if (ft_strlen(special) > 2)
			str_exit_status = (ft_strjoin2(str_exit_status, special + 2));
		return (free(special), str_exit_status);
	}
	else
		return (is_special_dollar(special, number_of_char(special, '$'), 0));
}


