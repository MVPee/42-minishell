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
	int			flag;
}				t_signal;

extern t_signal	g_sig;

char			*get_str_readline(void);
void			init_signal(void);
void			signal_heredoc(int signum);
void			signal_quit(int signum);
void			signal_handler(int signum);

#endif