/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-pee <mvan-pee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 18:18:05 by mvpee             #+#    #+#             */
/*   Updated: 2024/02/29 12:52:47 by mvan-pee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static t_lexer *lexer_parsing(char *str)
{
	char	**split;
	int		i;
	bool	flag;
	t_lexer	*cmd;
	t_node	*node;

	i = -1;
	split = ft_split(str, " ");
	cmd = ft_lexer_new(str);
	node = NULL;
	while (split[++i])
	{
		if (!ft_strcmp(split[i], "<<"))
			flag = ft_node_add(&node, ft_node_new(split[++i], HEREDOC));
		else if (!ft_strcmp(split[i], "<"))
			flag = ft_node_add(&node, ft_node_new(split[++i], INPUT));
		else if (!ft_strcmp(split[i], ">"))
			flag = ft_node_add(&node, ft_node_new(split[++i], OUTPUT));
		else if (!ft_strcmp(split[i], ">>"))
			flag = ft_node_add(&node, ft_node_new(split[++i], APPEND));
		else
			flag = ft_node_add(&node, ft_node_new(split[i], CMD));
		if (!flag)
			return (NULL);
	}
	cmd->head = node;
	return (cmd);
}

t_lexer	*ft_lexer(char *line, t_data *data, t_env *env)
{
	char	**split;
	int		i;
	t_lexer	*head = NULL;
	t_lexer	*lexer = NULL;
	char *new_line;

	if (!(new_line = checker(line, env, *data)))
		return (data->env_var = 2, NULL);
	if (!ft_strcmp(new_line, "\0"))
		return (NULL);
	i = -1;
	split = ft_split(new_line, "|");
	while (split[++i])
	{
		lexer = lexer_parsing(split[i]);
		if (!lexer)
			free_lexer(lexer);
		ft_lexer_add(&head, lexer);
	}
	return (head);
}