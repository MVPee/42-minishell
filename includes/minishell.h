/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 21:35:59 by mvpee             #+#    #+#             */
/*   Updated: 2024/02/13 13:46:04 by mvpee            ###   ########.fr       */
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
# include "stdbool.h"
# include <readline/readline.h>

typedef struct s_env
{
	int		shell_level;
	int 	var_env; // $?
	char	*pwd;
	char	**path;
	char 	**env; //With the correct shell level (need to implements)
}			t_env;

// Buildins
void		ft_echo(t_env env, char **split);
void		ft_env(t_env env, char **split);

#endif