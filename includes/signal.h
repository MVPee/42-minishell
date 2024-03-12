/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:13:36 by nechaara          #+#    #+#             */
/*   Updated: 2024/03/11 17:40:54 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
# define SIGNAL_H

typedef struct s_signal
{
	bool		flag;
	bool		execve;
	bool		heredoc;
	bool		minishell;
	bool		flag_heredoc;
}				t_signal;

extern t_signal	g_sig;

char			*get_str_readline(void);
void			init_signal(t_data *data);
void			signal_heredoc(int signum);
void			signal_heredoc2(int signum);

#endif