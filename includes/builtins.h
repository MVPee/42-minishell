/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:45:36 by mvpee             #+#    #+#             */
/*   Updated: 2024/03/09 15:09:30 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../srcs/libft/includes/libft.h"
# include "minishell.h"

// Builtins
char	*builtins(t_env **head, t_data *data, t_parsing parsing);
bool	isbuiltins(char *line);
bool	isspecial(t_parsing parsing);
void	ft_echo(t_data *data, char **split);
void	ft_env(t_data *data, t_env *head, char **split);
void	ft_pwd(t_data *data, t_env **head);
void	ft_unset(t_env **head, t_data *data, char **split);
void	ft_export(t_env **head, t_data *data, char **split);
void	ft_cd(t_env *head, t_data *data, char **split);
void	ft_exit(t_env *head, t_data *data, char **split);

// Builtsins Utils
bool	is_key_valid(char *str);
void	ft_sorted_env(t_env *head);
char	*reconstructed_entry(char *s1, char *s2);
void	*non_valid_arg(char *line);
void	error_handler_export(char *s1, char *s2);
void	env_entry_update(t_env **head, char *clean_entry);

#endif