/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_support.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldehaudt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 00:08:52 by ldehaudt          #+#    #+#             */
/*   Updated: 2018/09/08 00:08:55 by ldehaudt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	startup_env(int i, char **b, char **envp)
{
	i = 0;
	(void)b;
	while (envp[i])
	{
		set_env_var(envp[i]);
		i++;
	}
}

char	**make_env_array(void)
{
	int		i;
	t_env	*tmp;
	char	**arr;
	char	*s1;
	char	*s2;

	tmp = g_env;
	i = 0;
	while (tmp)
	{
		tmp = tmp->nxt;
		i++;
	}
	arr = malloc(sizeof(char*) * (i + 1));
	arr[i] = NULL;
	tmp = g_env;
	i = 0;
	while (tmp)
	{
		s1 = ft_strmerge(ft_mallocstr(tmp->name), ft_mallocstr("="));
		s2 = ft_mallocstr(tmp->contents);
		arr[i++] = ft_strmerge(s1, s2);
		tmp = tmp->nxt;
	}
	return (arr);
}

void	free_env_array(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
