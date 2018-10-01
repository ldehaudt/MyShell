/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldehaudt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 00:12:21 by ldehaudt          #+#    #+#             */
/*   Updated: 2018/09/08 00:12:23 by ldehaudt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(char *param)
{
	size_t	i;
	char	**words;
	char	*tmp;

	words = split_params(param);
	i = 0;
	while (words[i])
	{
		if (words[i][0] == '$')
		{
			tmp = ft_strsub(words[i], 1, ft_strlen(words[i]) - 1);
			if (get_env_var(tmp))
				ft_putstr(get_env_var(tmp)->contents);
			free(tmp);
		}
		else
			ft_putstr(words[i]);
		i++;
		if (words[i])
			ft_putchar(' ');
	}
	ft_putchar('\n');
	free(words);
	free(param);
}

void	cd_cont(char **path)
{
	char *tmp;

	tmp = NULL;
	if (ft_strcmp(path[0], "-") == 0)
		if (get_env_var("OLDPWD"))
			chdir(get_env_var("OLDPWD")->contents);
		else
			ft_putstr("cd: OLDPWD env var not found.\n");
	else if (path[0][0] == '~')
		if (get_env_var("HOME"))
		{
			path[0][0] = '/';
			tmp = ft_strmerge(ft_mallocstr(get_env_var("HOME")->contents),
		ft_mallocstr(path[0]));
			chdir(tmp);
		}
		else
			ft_putstr("cd: HOME env var not found.\n");
	else if (chdir(path[0]) == -1)
	{
		ft_putstr("cd: no such file or directory: ");
		ft_putendl(path[0]);
	}
	free(tmp);
}

void	cd(char *pth)
{
	char **path;
	char *str;
	char buf[BUFF];

	path = split_params(pth);
	str = NULL;
	if (get_env_var("PWD"))
		str = ft_strmerge(ft_mallocstr("OLDPWD "),
			ft_mallocstr(get_env_var("PWD")->contents));
	if (ft_strlen(path[0]) == 0)
	{
		if (get_env_var("HOME"))
			chdir(get_env_var("HOME")->contents);
		else
			ft_putstr("cd: HOME env var not found.\n");
	}
	else
		cd_cont(path);
	set_env_var(str);
	str = ft_strmerge(ft_mallocstr("PWD "), ft_mallocstr(getcwd(buf, 500)));
	set_env_var(str);
	free(path);
	free(pth);
}

void	exit_func(char *param)
{
	free(param);
	exit(0);
}
