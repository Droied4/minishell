/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 10:37:32 by avolcy            #+#    #+#             */
/*   Updated: 2024/04/27 11:11:45 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*my_allocation(size_t len)
{
	char	*allocated;

	allocated = malloc(sizeof(char) * len + 1);
	if (!allocated)
		return (NULL);
	allocated[0] = '\0';
	return (allocated);
}

char	*is_special_dollar(char *data, int i)
{
	int		num_dollar;
	pid_t	pid;
	char	*print_pid;

	pid = getpid();
	print_pid = NULL;
	num_dollar = number_of_quotes(data, '$');
	while (i++ < num_dollar / 2)
		print_pid = ft_strjoin2(print_pid, ft_itoa((int)pid));
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
	return (print_pid);
}

char	*special_cases(char *special, int exit_status)
{

	if (!ft_strncmp("$?", special, 2))
	{
		if (ft_strlen(special) > 2)
			return (ft_strjoin2(ft_itoa(exit_status), special + 2));
		return (ft_itoa(exit_status));
	}
	else
		return (is_special_dollar(special, 0));
}

/*''holas'''    len = 10   formula is ((len + (quote % 2)) - quotes
 10 + 5 % 2 - 5 = 10 + 1 - 5 = 6*/
char	*remove_uneven(char *str, char quote, int num_quotes)
{
	int		j;
	size_t	i;
	char	*tmp;

	i = 1;
	j = 0;
	tmp = my_allocation(ft_strlen(str));
	while (*str != '\0')
	{
		if (*str != quote)
		{
			i++;
			tmp[j++] = *str;
		}
		else if (*str == quote && i == ft_strlen(str) + (num_quotes % 2)
			- num_quotes)
			tmp[j++] = *str;
		str++;
	}
	tmp[j] = '\0';
    printf("inside of remove uneven add is {%p}\n", str);
	return (tmp);
}

char	*remove_char(char *str, char quote, int j)
{
	char	*tmp;
	int		num_quotes;

	tmp = my_allocation(ft_strlen(str));
	num_quotes = number_of_quotes(str, quote);
	if (num_quotes % 2 == 0 || quote == DQUOT)
	{
		while (*str != '\0')
		{
			if (!(*str == quote))
				tmp[j++] = *str;
			str++;
		}
	}
	else if (num_quotes % 2 != 0)
		return (remove_uneven(str, quote, num_quotes));
	tmp[j] = '\0';
    printf("inside of remove char add is {%p}\n", str);

	return (tmp);
}
