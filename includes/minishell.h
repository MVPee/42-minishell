/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 21:35:59 by mvpee             #+#    #+#             */
/*   Updated: 2024/02/15 15:15:01 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define RESET "\x1b[0m"
# define BOLD "\x1b[1m"
# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define YELLOW "\x1b[33m"
# define BLUE "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN "\x1b[36m"
# define WHITE "\x1b[37m"

# include "../srcs/libft/includes/libft.h"
# include "error.h"
# include <readline/readline.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <readline/history.h>

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
	struct s_env	*prv;
}					t_env;

typedef struct s_data
{
	int				env_var;
}					t_data;

// env init
t_env				*env_init(char **envs);

// env operation
char				**env_to_tab(t_env *head);
t_env				*tab_to_env(char **envp);
size_t				get_size(t_env *head);
void				env_remove_entry(t_env **head, char *key);
t_env				*find_key(t_env *head, char *key);
char				*get_value(t_env *target_node);
t_env				*remove_top_node(t_env **head);
t_env				*get_last_entry(t_env **head);

// Buildins
void				ft_echo(t_data *data, char **split);
void				ft_env(t_data *data, t_env *head, char **split);
void				ft_pwd(t_data *data, t_env *head);
void ft_unset(t_env *head, t_data *data, char **split);

#endif