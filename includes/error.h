/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 12:39:03 by nechaara          #+#    #+#             */
/*   Updated: 2024/03/17 20:12:15 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

// GLOBAL CODE
# define SUCCESSFUL_COMMAND 0
# define UNSUCCESSFUL_COMMAND 1
// ENV VARIABLE CODES
# define MISSING_RIGHTS 126
# define COMMAND_NOT_FOUND 127
# define COMMAND_INTERRUPTED 130
# define COMMAND_INTERRUPTED_QUIT 130
// EXIT RELATED ERROR CODES
# define NUMERICAL_ARGUMENT_NESCESSARY 2
# define TOO_MANY_ARGUMENTS 1

#endif