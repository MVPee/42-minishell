/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:45:36 by mvpee             #+#    #+#             */
/*   Updated: 2024/03/07 10:47:25 by mvpee            ###   ########.fr       */
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
void	*error_arguments_without_equal(char *line);
void	error_handler_export(char *s1, char *s2);

#endif