/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldehaudt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 00:33:30 by ldehaudt          #+#    #+#             */
/*   Updated: 2018/09/08 00:33:31 by ldehaudt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <unistd.h>
# include <stdbool.h>
# include <stdlib.h>

# define BUFF 5000
# define ISEMPTY(x) (x == ' ' || x == '\t')

typedef struct	s_disp{
	char			*code;
	void			(*func)(char *params);
}				t_disp;

typedef struct	s_env{
	char			*name;
	char			*contents;
	void			*free_ptr;
	struct s_env	*nxt;
}				t_env;

bool				g_done;
t_env				*g_env;

void			cd(char *pth);
void			echo(char *param);
void			exit_func(char *param);
void			show_env(char *param);
void			set_env_var(char *str);
void			unset_env_var(char *var);
void			echo(char *param);
void			cd_cont(char **path);
void			cd(char *pth);
void			exit_func(char *param);
int				word_length(char *param, int pos);
bool			is_word_start(char *param, int pos);
int				count_args(char *param);
char			**split_params(char *param);
char			*ft_mallocstr(char *str);
char			*ft_strmerge(char *restrict s1, char *restrict s2);
bool			format(char *str);
t_env			*get_env_var(char *var);
void			unset_env_var(char *in);
void			show_env(char *param);
void			make_env(char **params, bool b, char *str);
void			set_env_var(char *str);
void			startup_env(int i, char **b, char **envp);
char			**make_env_array(void);
void			free_env_array(char **arr);

#endif
