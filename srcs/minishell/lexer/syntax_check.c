/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-pee <mvan-pee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:52:14 by mvpee             #+#    #+#             */
/*   Updated: 2024/03/12 16:01:29 by mvan-pee         ###   ########.fr       */
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
static int syntax_check_in(char *line, int *i)
{
	if (line[(*i)] == '<')
	{
		if (line[(*i) + 1] == '>')
			return (ft_printf("syntax error near unexpected token '<'\n"));
		if (line[(*i) + 1] == '<')
		{
			(*i) = (*i) + 2;
			while (line[(*i)] == ' ')
				(*i)++;
			if (ft_ischarin(line[(*i)], "<>|") || !line[(*i)])
				return (ft_printf("syntax error near unexpected token '<'\n"));
		}
		else
		{
			(*i)++;
			while (line[(*i)] == ' ')
				(*i)++;
			if (ft_ischarin(line[(*i)], "<>|") || !line[(*i)])
				return (ft_printf("syntax error near unexpected token '<'\n"));
		}
		(*i)--;
	}
	return (0);
}

static bool check_after_redirection(char *line, int i)
{
	bool flag;
	
	flag = false;
	if (line[i] == '\'')
	{
		i++;
		while(line[i] != '\'')
		{
			if (ft_isprint(line[i]) && line[i] != '\'')
				flag = true;
			i++;
		}
		if (flag)
			return (false);
		if (!line[i])
			return (true);
	}
	return (false);
}

static int syntax_check_out(char *line, int *i)
{
	if (line[(*i)] == '>')
	{
		if (line[(*i) + 1] == '<')
			return (ft_printf("syntax error near unexpected token '>'\n"));
		if (line[(*i) + 1] == '>')
		{
			(*i) = (*i) + 2;
			while (line[(*i)] == ' ')
				(*i)++;
			if (ft_ischarin(line[(*i)], "<>|") || !line[(*i)])
				return (ft_printf("syntax error near unexpected token '>'\n"));
		}
		else
		{
			(*i)++;
			while (line[(*i)] == ' ')
				(*i)++;
			if (ft_ischarin(line[(*i)], "<>|") || !line[(*i)])
				return (ft_printf("syntax error near unexpected token '>'\n"));
			if (check_after_redirection(line, *i))
				return (ft_printf("syntax error near unexpected token '>' 2\n"));
		}
		i--;
	}
    return (0);
}

static int syntax_check2(char *line, int *i)
{
	if (line[(*i)] == '\"')
	{
		(*i)++;
		while (line[(*i)] && line[(*i)] != '\"')
			(*i)++;
		if (!line[(*i)])
			return (ft_printf("syntax error unclosed \" token\n"));
	}
	else if (line[(*i)] == '\'')
	{
		(*i)++;
		while (line[(*i)] && line[(*i)] != '\'')
			(*i)++;
		if (!line[(*i)])
			return (ft_printf("syntax error unclosed \' token\n"));
	}
	else if (line[(*i)] == ';')
		return (ft_printf("syntax error near unexpected token ';'\n"));
	else if (line[(*i)] == '|')
	{
		if (check_before(line, (*i)))
			return (ft_printf("syntax error near unexpected token '|'\n"));
		if (check_after(line, (*i)))
			return (ft_printf("syntax error near unexpected token '|'\n"));
	}
	return (0);
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
		if (syntax_check_in(line, &i))
			return (ft_free(1, &line), true);
		if (syntax_check_out(line, &i))
			return (ft_free(1, &line), true);
		if (syntax_check2(line, &i))
			return (ft_free(1, &line), true);
		if (!line[i])
			break ;
	}
	ft_printf("Syntax good\n");
	return (ft_free(1, &line), false);
}
