/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldehaudt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 00:06:05 by ldehaudt          #+#    #+#             */
/*   Updated: 2018/09/08 00:06:06 by ldehaudt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		word_length(char *param, int pos)
{
	int len;
	int s;
	int d;

	s = 0;
	d = 0;
	len = 0;
	if (param[pos] == '\'' || param[pos] == '"')
		len--;
	while (param[pos])
	{
		if (param[pos] == '\'')
			s++;
		if (param[pos] == '"')
			d++;
		if (param[pos] == '"' || param[pos] == '\'' || ISEMPTY(param[pos]))
			if (s % 2 == 0 && d % 2 == 0)
				return (len);
		len++;
		pos++;
	}
	if (s % 2 == 0 && d % 2 == 0)
		return (len);
	return (-1);
}

bool	is_word_start(char *param, int pos)
{
	int s;
	int d;
	int i;

	i = 0;
	s = 0;
	d = 0;
	while (i < pos)
	{
		if (param[i] == '\'')
			s++;
		if (param[i] == '"')
			d++;
		i++;
	}
	if (d % 2 == 1 || s % 2 == 1)
		return (false);
	if (!ISEMPTY(param[i]) && (i == 0 || ISEMPTY(param[i - 1])))
		return (true);
	return (false);
}

int		count_args(char *param)
{
	int i;
	int num;

	num = 0;
	i = 0;
	while (param[i])
	{
		if (is_word_start(param, i))
			num++;
		i++;
	}
	return (num);
}

char	**split_params(char *param)
{
	char	**out;
	int		*len;
	int		i;
	int		count;

	out = (char**)malloc((count_args(param) + 1) * sizeof(char*));
	len = (int*)malloc(count_args(param) * sizeof(int));
	i = -1;
	count = 0;
	while (param[++i])
		if (is_word_start(param, i))
		{
			if (param[i] == '"' || param[i] == '\'')
				out[count] = &(param[i + 1]);
			else
				out[count] = &(param[i]);
			len[count] = word_length(param, i);
			count++;
		}
	out[count] = 0;
	i = count;
	while (--i >= 0)
		out[i][len[i]] = 0;
	free(len);
	return (out);
}
