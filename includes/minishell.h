/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 21:35:59 by mvpee             #+#    #+#             */
/*   Updated: 2024/03/14 01:04:14 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define RESET "\x1b[0m"
# define BOLD "\x1b[1m"
# define RED "\x1b[31m"
# define RED2 "\033[0;31m"
# define GREEN "\x1b[32m"
# define YELLOW "\x1b[33m"
# define BLUE "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN "\x1b[36m"
# define WHITE "\x1b[37m"
# define BLACK "\033[30m"
# define LONG_MAX_STRING "9223372036854775807"
# define LONG_MIN_STRING "-9223372036854775808"
# define EXECUTABLE_NAME "./minishell"

# include "../srcs/libft/includes/libft.h"
# include "struct.h"
# include "error.h"
# include "lexer.h"
# include "parsing.h"
# include "builtins.h"
# include "signal.h"
# include "executor.h"
# include <stdio.h>
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <sys/wait.h>

// Env Init
t_env	*env_init(char **envs);

// Env Operations
char	**env_to_tab(t_env *head);
char	**env_split(char *env);
t_env	*tab_to_env(char **envp);
t_env	*env_add_entry(t_env *head, char *entry);
t_env	*env_remove_entry(t_env **head, char *key);
t_env	*find_key(t_env *head, char *key);
char	*get_value(t_env *target_node);
t_env	*remove_top_node(t_env **head);
t_env	*get_last_entry(t_env **head);
void	write_value(t_env **head, char *key, char *value);
void	free_env_list(t_env *head);
void	shell_lvl_handler(t_env *head);
void	update_content_of_node(t_env **created_node, char **splitted_arguments);
char	*no_null_join(char *s1, char *s2);
t_env	*minimal_env(void);
void	free_env_element(t_env *node);

#endif