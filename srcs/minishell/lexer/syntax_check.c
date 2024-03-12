/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-pee <mvan-pee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:52:14 by mvpee             #+#    #+#             */
/*   Updated: 2024/03/12 11:48:33 by mvan-pee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static bool	check_after(char *line, int i)
{
	int	j;

	j = i;
	while (line[++j])
	{
		while (line[j] == ' ')
			j++;
		if (ft_isprint(line[j]))
			return (false);
		else if (line[j] == '|')
			return (true);
		else if (!line[j])
			return (true);
	}
	return (true);
}

static bool	check_before(char *line, int i)
{
	int	j;

	j = i;
	if (j == 0)
		return (true);
	while (line[--j])
	{
		while (line[j] == ' ')
			j--;
		if (ft_isprint(line[j]))
			return (false);
		else if (line[j] == '|')
			return (true);
		else if (!line[j])
			return (true);
		if (j == 0)
			return (true);
	}
	return (false);
}

bool	syntax_check(char *str)
{
	int		i;
	char	*line;

	line = ft_strtrim(str, " ");
	if (!line)
		return (true);
	i = -1;
	while (line[++i])
	{
		if (line[i] == '\"')
		{
			i++;
			while (line[i] && line[i] != '\"')
				i++;
			if (!line[i])
				return (ft_printf("syntax error unclosed \" token\n"), true);
		}
		else if (line[i] == '\'')
		{
			i++;
			while (line[i] && line[i] != '\'')
				i++;
			if (!line[i])
				return (ft_printf("syntax error unclosed \' token\n"), true);
		}
		else if (line[i] == ';')
			return (ft_printf("syntax error near unexpected token ';'\n", \
					true));
		else if (line[i] == '|')
		{
			if (check_before(line, i))
				return (ft_printf("syntax error near unexpected token '|'\n"), \
					true);
			if (check_after(line, i))
				return (ft_printf("syntax error near unexpected token '|'\n"), \
					true);
		}
		else if (line[i] == '<')
		{
			if (line[i + 1] == '>')
				return (ft_printf("syntax error near unexpected token <'\n"), \
						true);
			if (line[i + 1] == '<')
			{
				i = i + 2;
				while (line[i] == ' ')
					i++;
				if (ft_ischarin(line[i], "<>|") || !line[i])
					return (ft_printf("syntax error near unexpected token '<'\n"), \
						true);
			}
			else
			{
				i++;
				while (line[i] == ' ')
					i++;
				if (ft_ischarin(line[i], "<>|") || !line[i])
					return (ft_printf("syntax error near unexpected token '<'\n"), \
						true);
			}
			i--;
		}
		else if (line[i] == '>')
		{
			if (line[i + 1] == '<')
				return (ft_printf("syntax error near unexpected token '>'\n"), \
					true);
			if (line[i + 1] == '>')
			{
				i = i + 2;
				while (line[i] == ' ')
					i++;
				if (ft_ischarin(line[i], "<>|") || !line[i])
					return (ft_printf("syntax error near unexpected token '>'\n"), \
						true);
			}
			else
			{
				i++;
				while (line[i] == ' ')
					i++;
				if (ft_ischarin(line[i], "<>|") || !line[i])
					return (ft_printf("syntax error near unexpected token '>'\n"), \
						true);
			}
			i--;
		}
		if (!line[i])
			break ;
	}
	free(line);
	return (false);
}
