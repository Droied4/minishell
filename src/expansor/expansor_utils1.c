/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 13:12:42 by avolcy            #+#    #+#             */
/*   Updated: 2024/05/31 21:28:22 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*aux_trim(char *data)
{
	int	pos_dquote;
	int	pos_squote;

	pos_dquote = char_is_inside(data, DQUOT);
	pos_squote = char_is_inside(data, SQUOT);
	if (pos_dquote < 0 && pos_squote >= 0)
		return (trimmer_quotes(data, SQUOT));
	else if (pos_squote < 0 && pos_dquote >= 0)
		return (trimmer_quotes(data, DQUOT));
	if (pos_dquote > 0 && pos_dquote > pos_squote)
		return (trimmer_quotes(data, SQUOT));
	else if (pos_squote > 0 && pos_squote > pos_dquote)
		return (trimmer_quotes(data, DQUOT));
	return (ft_strdup(""));
}

char	**split_env_var(char *str)
{
	int		i;
	int		len;
	int		position;
	char	**splitted;

	len = count_len(str);
	splitted = malloc(sizeof(char *) * (len + 1));
	i = 0;
	while (i < len)
	{
		splitted[i] = find_env_part(str, &position);
		str = &str[position];
		i++;
	}
	splitted[i] = NULL;
	return (splitted);
}

char	*find_env_part(char *str, int *pos)
{
	int		i;
	int		len;
	char	*part;

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

/*char	*is_special_dollar(char *data, int num_dollar, int i)
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
}*/

int is_special_cases(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && str[i + 1] == '?')
			return (i);
		i++;
	}
	return (0);
}
int how_many_dol_interog(char *str)
{
	int i;
	int number;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && str[i + 1] == '?')
			number += 1;
		i++;
	}
	return (number);
}

// int len_part(char *str)
// {
//     int i;
//     int len;

//     i = 0;
//     len = 0;
//     while (str[i])
//     {
      
//       if(str[i] == '$' && str[i + 1] && str[i + 1] == '?')
//         return (2);
//       else
//         len++;
//       i++;
//     }
//     return(len);
// }

// #include <stdio.h>
// int main() {
//   int len = 0;
//   char *s = "h$l$?1??$?4";
  
//   while (*s)
//   {
//     len = len_part(s);
//     printf("%d\n", len);
//     s = &s[len];
//     len = 0;
//   }
//   return 0;
// }

char *small_part(char *str, int *pos)
{
	int i;
	int len;
	char *part;

	len = len_part(str);
	*pos = len;
	part = malloc(sizeof(char) * len + 1);
	if (!part)
		return (NULL);
	i = -1;
	while (++i < len)
		part[i] = str[i];
	part[i] = '\0';
	return (part);
}

char	**split_dollar_interog(char *str)
{
	int i;
	int pos;
	char **result;
	int num_dol_int;

	i = -1;
	num_dol_int = how_many_dol_interog(str);
	result = malloc(sizeof(char *) * num_dol_int + 1);
	if (!result)
		return (NULL);
	pos = 0;
	while (++i < num_dol_int)
	{
		result[i] = small_part(str, &pos);
		str = &str[pos];
		i++;
	}
	result[i] = NULL;
	return (result);
}

char	*special_cases(char *special, int exit_status)
{
	int i;
	char  *str_exit;
	char **split_exit;

	i = 0;
	str_exit = ft_itoa(exit_status);
	split_exit = split_dollar_interog(special);
	while (split_exit[i])
	{
		if (!ft_strncmp("$?", split_exit[i], 3))
			split_exit[i] = ft_strdup(str_exit);
		i++;
	}
	free(str_exit);
	str_exit = join_split(split_exit);
	free_matrix(split_exit);
	return (str_exit);
}

// char	*special_cases(char *special, int exit_status)
// {
// 	char	*str_exit_status;

// 	if (!ft_strncmp("$?", special, 2))
// 	{
// 		str_exit_status = ft_itoa(exit_status);
// 		if (ft_strlen(special) > 2)
// 			str_exit_status = (ft_strjoin2(str_exit_status, special + 2));
// 		return (free(special), str_exit_status);
// 	}
// 	else
// 		return (ft_strdup(special));
// }
