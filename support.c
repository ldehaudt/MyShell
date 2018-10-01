/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldehaudt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 00:05:56 by ldehaudt          #+#    #+#             */
/*   Updated: 2018/09/08 00:05:58 by ldehaudt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_mallocstr(char *str)
{
	char *n;

	n = ft_memalloc(ft_strlen(str) + 1);
	ft_strcpy(n, str);
	return (n);
}

char	*ft_strmerge(char *restrict s1, char *restrict s2)
{
	int		index;
	int		count;
	char	*str;
	int		i;

	i = 0;
	str = ft_memalloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	count = 0;
	index = ft_strlen(s1);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[count])
	{
		str[index] = s2[count];
		index++;
		count++;
	}
	str[index] = '\0';
	free(s1);
	free(s2);
	return (str);
}

bool	format(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] != ' ')
	{
		if (str[i] == '=')
		{
			str[i] = ' ';
			return (true);
		}
		i++;
	}
	return (false);
}
