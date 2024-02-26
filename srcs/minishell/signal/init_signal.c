/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:29:06 by mvpee             #+#    #+#             */
/*   Updated: 2024/02/26 13:54:58 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void sigint_handler()
{
	char *line;

	line = get_str_readline();
	ft_printf(("\n%s"), line);
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