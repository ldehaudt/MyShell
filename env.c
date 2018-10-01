/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldehaudt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 00:05:47 by ldehaudt          #+#    #+#             */
/*   Updated: 2018/09/08 00:05:49 by ldehaudt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*get_env_var(char *var)
{
	t_env *tmp;

	tmp = g_env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, var) == 0)
		{
			return (tmp);
		}
		tmp = tmp->nxt;
	}
	return (NULL);
}

void	unset_env_var(char *in)
{
	t_env	*tmp;
	t_env	*prev;
	char	*var;

	prev = NULL;
	tmp = g_env;
	var = ft_strtrim(in);
	free(in);
	while (tmp)
	{
		if (ft_strcmp(tmp->name, var) == 0)\
		{
			if (prev == NULL)
			{
				g_env = tmp->nxt;
			}
			else
				prev->nxt = tmp->nxt;
			free(tmp->free_ptr);
			free(tmp);
		}
		prev = tmp;
		tmp = tmp->nxt;
	}
	free(var);
}

void	show_env(char *param)
{
	t_env *tmp;

	tmp = g_env;
	while (tmp)
	{
		ft_putstr(tmp->name);
		ft_putstr("=");
		ft_putstr(tmp->contents);
		ft_putstr("\n");
		tmp = tmp->nxt;
	}
	free(param);
}

void	make_env(char **params, bool b, char *str)
{
	t_env	*tmp;

	if ((tmp = get_env_var(params[0])))
	{
		free(tmp->free_ptr);
		tmp->free_ptr = str;
		tmp->name = params[0];
		tmp->contents = params[1];
	}
	else
	{
		tmp = (t_env*)malloc(sizeof(t_env));
		tmp->free_ptr = (b == true ? NULL : str);
		tmp->name = params[0];
		tmp->contents = params[1];
		tmp->nxt = g_env;
		g_env = tmp;
	}
}

void	set_env_var(char *str)
{
	char	**params;
	int		i;
	bool	b;

	if (!str)
		return ;
	b = format(str);
	params = split_params(str);
	i = 0;
	while (params[i])
		i++;
	if (i != 2)
	{
		ft_putstr("Invalid Parameters.\n");
		return ;
	}
	make_env(params, b, str);
	free(params);
}
