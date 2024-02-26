/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:29:06 by mvpee             #+#    #+#             */
/*   Updated: 2024/02/26 13:47:21 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void sigint_handler()
{
	char *line;

	line = get_str_readline();
	ft_printf(("%s\n"), line);
	free(line);
}

void sigterm_handler()
{
	ft_printf("exit\n");
	exit(0);
}

void init_signal(void)
{
    if (signal(SIGINT, sigint_handler) == SIG_ERR)
    {
        perror("signal(SIGINT)");
        exit(EXIT_FAILURE);
    }
	if (signal(SIGTERM, sigterm_handler) == SIG_ERR)
    {
        perror("signal(SIGTERM)");
        exit(EXIT_FAILURE);
    }
}