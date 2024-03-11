/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-pee <mvan-pee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:48:04 by mvpee             #+#    #+#             */
/*   Updated: 2024/03/11 12:49:27 by mvan-pee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_data
{
	int				env_var;
	int				nbr_cmd;
	pid_t			*pid;
	int				**pipefds;
	bool			flag;
}					t_data;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
	struct s_env	*prv;
}					t_env;

#endif