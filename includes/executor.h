/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 21:18:31 by mvpee             #+#    #+#             */
/*   Updated: 2024/03/11 21:19:17 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

void	executor(t_env **head, t_data *data, t_parsing *parsing);
void	child_executor(t_env **head, t_data *data, t_parsing *parsing);

#endif