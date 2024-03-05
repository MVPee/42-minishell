/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 18:18:05 by mvpee             #+#    #+#             */
/*   Updated: 2024/03/05 13:37:37 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_node	*new_node(char *name, t_token token)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		exit(1);
	node->name = strdup(name);
	node->token = token;
	node->next = NULL;
	return (node);
}

void	append_node(t_node **head, char *name, t_token token)
{
	t_node	*new;
	t_node	*current;

	new = new_node(name, token);
	if (*head == NULL)
		*head = new;
	else
	{
		current = *head;
		while (current->next != NULL)
			current = current->next;
		current->next = new;
	}
}

static t_lexer	set_lexer(char *str, t_env *env, t_data data)
{
	t_lexer	new_lexer;
	t_node	*head;
	int		i;
	char	buffer[10000];
	int		j;
	char	buffer2[100];
	int		k;

	new_lexer.cmd = NULL;
	new_lexer.head = NULL;
	head = NULL;
	i = -1;
	j = 0;
	k = 0;
	while (str[++i])
	{
		if (str[i] == '\"')
		{
			buffer[j++] = str[i++];
			while (str[i] != '\"' && str[i])
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
			while (str[i] != '\'' && str[i])
			{
				buffer[j] = str[i];
				i++;
				j++;
			}
			buffer[j++] = str[i];
		}
		// INPUT
		else if (str[i] == '<')
		{
			i++;
			// HEREDOC
			if (str[i] == '<')
			{
				i++;
				while (str[i] == ' ')
					i++;
				while (str[i] != ' ' && str[i])
				{
					if (str[i] == '\'')
					{
						buffer2[k++] = str[i++];
						while (str[i] != '\'' && str[i])
						{
							buffer2[k] = str[i];
							k++;
							i++;
						}
						buffer2[k++] = str[i++];
					}
					else if (str[i] == '\"')
					{
						buffer2[k++] = str[i++];
						while (str[i] != '\"' && str[i])
						{
							buffer2[k] = str[i];
							k++;
							i++;
						}
						buffer2[k++] = str[i++];
					}
					else
						buffer2[k++] = str[i++];
				}
				buffer2[k] = '\0';
				append_node(&(new_lexer.head), buffer2, HEREDOC);
				ft_memset(buffer2, 0, 100);
				k = 0;
			}
			else
			{
				while (str[i] == ' ')
					i++;
				while (str[i] != ' ' && str[i])
				{
					if (str[i] == '\'')
					{
						buffer2[k++] = str[i++];
						while (str[i] != '\'' && str[i])
						{
							buffer2[k] = str[i];
							k++;
							i++;
						}
						buffer2[k++] = str[i++];
					}
					else if (str[i] == '\"')
					{
						buffer2[k++] = str[i++];
						while (str[i] != '\"' && str[i])
						{
							buffer2[k] = str[i];
							k++;
							i++;
						}
						buffer2[k++] = str[i++];
					}
					else
						buffer2[k++] = str[i++];
				}
				buffer2[k] = '\0';
				append_node(&(new_lexer.head), parsing_cmd(buffer2, env, data)[0], INPUT);
				ft_memset(buffer2, 0, 100);
				k = 0;
			}
			i--;
		}
		// OUTPUT
		else if (str[i] == '>')
		{
			i++;
			// APPEND
			if (str[i] == '>')
			{
				i++;
				while (str[i] == ' ')
					i++;
				while (str[i] != ' ' && str[i])
				{
					if (str[i] == '\'')
					{
						buffer2[k++] = str[i++];
						while (str[i] != '\'' && str[i])
						{
							buffer2[k] = str[i];
							k++;
							i++;
						}
						buffer2[k++] = str[i++];
					}
					else if (str[i] == '\"')
					{
						buffer2[k++] = str[i++];
						while (str[i] != '\"' && str[i])
						{
							buffer2[k] = str[i];
							k++;
							i++;
						}
						buffer2[k++] = str[i++];
					}
					else
						buffer2[k++] = str[i++];
				}
				buffer2[k] = '\0';
				append_node(&(new_lexer.head), parsing_cmd(buffer2, env, data)[0], HEREDOC);
				ft_memset(buffer2, 0, 100);
				k = 0;
			}
			else
			{
				while (str[i] == ' ')
					i++;
				while (str[i] != ' ' && str[i])
				{
					if (str[i] == '\'')
					{
						buffer2[k++] = str[i++];
						while (str[i] != '\'' && str[i])
						{
							buffer2[k] = str[i];
							k++;
							i++;
						}
						buffer2[k++] = str[i++];
					}
					else if (str[i] == '\"')
					{
						buffer2[k++] = str[i++];
						while (str[i] != '\"' && str[i])
						{
							buffer2[k] = str[i];
							k++;
							i++;
						}
						buffer2[k++] = str[i++];
					}
					else
						buffer2[k++] = str[i++];
				}
				buffer2[k] = '\0';
				append_node(&(new_lexer.head), parsing_cmd(buffer2, env, data)[0], OUTPUT);
				ft_memset(buffer2, 0, 100);
				k = 0;
			}
			i--;
		}
		else
			buffer[j++] = str[i];
		if (!str[i])
			break ;
	}
	buffer[j] = '\0';
	new_lexer.cmd = ft_strdup(buffer);
	return (new_lexer);
}

t_lexer	*ft_lexer(char *line, t_data *data, t_env *env)
{
	char	**split;
	t_lexer	*lexer;
	int		count;
	int		i;

	count = 0;
	lexer = NULL;
	if (!line)
		return (NULL);
	if (!strcmp(line, "\0"))
		return (ft_free(1, &line), NULL);
	if (syntax_check(line))
		return (ft_free(1, &line), NULL);
	split = ft_splittrim(get_cmd_splitted(line, &count), " ");
	if (!split)
		return (ft_free(1, &line), NULL);
	lexer = malloc(sizeof(t_lexer) * count);
	if (!lexer)
		return (ft_free(1, &line), NULL);
	data->nbr_cmd = count;
	i = -1;
	while (++i < count)
		lexer[i] = set_lexer(split[i], env, *data);
	return (ft_free_matrix(1, &split), ft_free(1, &line), lexer);
}
