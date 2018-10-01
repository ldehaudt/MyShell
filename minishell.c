/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldehaudt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 23:57:08 by ldehaudt          #+#    #+#             */
/*   Updated: 2018/09/07 23:57:09 by ldehaudt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_disp g_disp[] = {
	{"echo", echo},
	{"cd", cd},
	{"env", show_env},
	{"setenv", set_env_var},
	{"unsetenv", unset_env_var},
	{"exit", exit_func},
	{NULL, NULL}
};

void	find_command(char **paths, char **param, char **env_arr)
{
	int i;

	paths = ft_strsplit(get_env_var("PATH")->contents, ':');
	i = -1;
	while (paths[++i])
	{
		paths[i] = ft_strmerge(paths[i], ft_mallocstr("/"));
		paths[i] = ft_strmerge(paths[i], ft_mallocstr(param[0]));
		execve(paths[i], param, env_arr);
	}
	ft_putstr("Unknown Command\n");
	exit(0);
}

void	command(char *str)
{
	pid_t	num;
	char	**param;
	char	**paths;
	char	**env_arr;

	param = split_params(str);
	env_arr = make_env_array();
	paths = NULL;
	num = fork();
	if (num != 0)
	{
		wait(NULL);
		free(paths);
		free(str);
		free(param);
		free_env_array(env_arr);
		return ;
	}
	else if (execve(param[0], param, env_arr) == -1 && get_env_var("PATH"))
	{
		find_command(paths, param, env_arr);
	}
	ft_putstr("Unknown Command\n");
	exit(0);
}

int		main(int ac, char **av, char **envp)
{
	char	*line;
	char	*par;
	int		i;

	startup_env(ac, av, envp);
	g_done = false;
	ft_putstr("\e[1;1H\e[2J");
	while (!g_done)
	{
		ft_putstr("$>");
		while (!get_next_line(0, &line))
			;
		i = -1;
		while (g_disp[++i].code != NULL)
			if (!ft_strncmp(g_disp[i].code, line, ft_strlen(g_disp[i].code)))
			{
				par = ft_strsub(line, ft_strlen(g_disp[i].code),
		ft_strlen(line) - ft_strlen(g_disp[i].code));
				free(line);
				g_disp[i].func(par);
				break ;
			}
		if (g_disp[i].code == NULL)
			command(line);
	}
}
