/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:46:20 by mvan-pee          #+#    #+#             */
/*   Updated: 2024/02/27 21:04:10 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*ft_echo(t_data *data, char **split)
{
    // int i = 0, j = 0;
    // bool flag;

    // flag = true;
    // if (split[1] && !ft_strcmp(split[1], "-n"))
    // {
    //     flag = false;
    //     i++;
    // }
    // while(split[++i])
    // {
    //     j = -1;
    //     while(split[i][++j])
    //     {
    //         if (split[i][j] == '$' && split[i][j + 1] == '?')
    //         {
    //             ft_printf("%d", data->env_var);
    //             j += 1;
    //         }
    //         else if (split[i][j] == '\\')
    //         {
    //             if (split[i][j + 1] == '\\')
    //             {
    //                 ft_printf("\\");
    //                 j += 1;
    //             }
    //         }
    //         else
    //             ft_printf("%c", split[i][j]);
    //     }
    //     if (split[i + 1] != NULL)
 	// 	    ft_printf(" ");
    // }
    // if (flag)
    //     ft_printf("\n");
    // data->env_var = 0;
    return (ft_strdup("Echo test\n"));
}
