/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 18:48:08 by nechaara          #+#    #+#             */
/*   Updated: 2024/02/19 00:24:13 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"
#include <asm-generic/errno-base.h>
#include <stddef.h>

static bool is_plus_before_equal(char *line)
{
    char    *split;
    
    if (split > line && *(split - 1) == 43)
        return (true);
    return (false);
}

char **ft_export_split(char *line, bool *do_concatenate)
{
   
}

