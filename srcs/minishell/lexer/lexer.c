/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 18:18:05 by mvpee             #+#    #+#             */
/*   Updated: 2024/03/03 15:34:10 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_node	*new_node(char *name, t_token token)
{
	t_node *node = malloc(sizeof(t_node));
	if (!node)
		exit(1);
	node->name = strdup(name);
	node->token = token;
	node->next = NULL;
	return node;
}

void	append_node(t_node **head, char *name, t_token token)
{
	t_node *new = new_node(name, token);
	if (*head == NULL)
		*head = new;
	else
	{
		t_node *current = *head;
		while (current->next != NULL)
			current = current->next;
		current->next = new;
	}
}

static t_lexer set_lexer(char *str)
{
	t_lexer new_lexer;
	new_lexer.cmd = NULL;
	new_lexer.head = NULL;
	t_node *head = NULL;
	
	int i = -1;
	char buffer[10000];
	int j = 0;
	char buffer2[100];
	int k = 0;

	while(str[++i])
	{
		if (str[i] == '\"')
		{
			buffer[j++] = str[i++];
			while(str[i] != '\"' && str[i])
			{
				buffer[j] = str[i];
				i++;
				j++;
			}
			buffer[j++] = str[i];
		}
		else if (str[i] == '\'')
		{
			buffer[j++] = str[i++];
			while(str[i] != '\'' && str[i])
			{
				buffer[j] = str[i];
				i++;
				j++;
			}
			buffer[j++] = str[i];
		}
		//INPUT
		else if (str[i] == '<')
		{
			i++;
			//HEREDOC
			if (str[i] == '<')
			{
				i++;
				while(str[i] == ' ')
					i++;
				while(ft_isprint(str[i]) && str[i] != ' ')
				{
					buffer2[k] = str[i];
					k++;
					i++;
				}
				buffer2[k] = '\0';
				append_node(&(new_lexer.head), buffer2, HEREDOC);
				ft_memset(buffer2, 0, 100);
				k = 0;
			}
			else
			{
				while(str[i] == ' ')
					i++;
				while(ft_isprint(str[i]) && str[i] != ' ')
				{
					buffer2[k] = str[i];
					k++;
					i++;
				}
				buffer2[k] = '\0';
				append_node(&(new_lexer.head), buffer2, INPUT);
				ft_memset(buffer2, 0, 100);
				k = 0;
			}
			i--;
		}
		//OUTPUT
		else if (str[i] == '>')
		{
			i++;
			//APPEND
			if (str[i] == '>')
			{
				i++;
				while(str[i] == ' ')
					i++;
				while(ft_isprint(str[i]) && str[i] != ' ')
				{
					buffer2[k] = str[i];
					k++;
					i++;
				}
				buffer2[k] = '\0';
				append_node(&(new_lexer.head), buffer2, APPEND);
				ft_memset(buffer2, 0, 100);
				k = 0;
			}
			else
			{
				while(str[i] == ' ')
					i++;
				while(ft_isprint(str[i]) && str[i] != ' ')
				{
					buffer2[k] = str[i];
					k++;
					i++;
				}
				buffer2[k] = '\0';
				append_node(&(new_lexer.head), buffer2, OUTPUT);
				ft_memset(buffer2, 0, 100);
				k = 0;
			}
			i--;
		}
		else
			buffer[j++] = str[i];
		if (!str[i])
			break;
	}
	buffer[j] = '\0';
	new_lexer.cmd = ft_strdup(buffer);
	return new_lexer;
} 

t_lexer	*ft_lexer(char *line, t_data *data, t_env *env)
{
	char	**split;
	t_lexer	*lexer;
	int count;
	int i;

	count = 0;
	lexer = NULL;
	if (!line)
		return (NULL);
	if (!strcmp(line, "\0"))
		return (ft_free(1, &line), NULL);
	if (check_after_pipe_and_semicolon(line))
		return (ft_free(1, &line), NULL);
	split = ft_splittrim(get_cmd_splitted(line, &count), " ");
	if (!split)
		return (ft_free(1, &line), NULL);
	lexer = malloc(sizeof(t_lexer) * count);
	if (!lexer)
		return (ft_free(1, &line), NULL);
	data->nbr_cmd = count;
	i = -1;
	while(++i < count)
		lexer[i] = set_lexer(split[i]);
	return (ft_free_matrix(1, &split), ft_free(1, &line), lexer);
}
