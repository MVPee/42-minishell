/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 14:16:17 by nechaara          #+#    #+#             */
/*   Updated: 2024/03/05 13:35:31 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	**env_split(char *env)
{
	char	**result;
	char	*split;
	size_t	len;

	split = ft_strchr(env, '=');
	if (!split || split == env)
		return (NULL);
	len = split - env;
	result = (char **)malloc(3 * sizeof(char *));
	if (!result)
		return (NULL);
	result[0] = ft_strndup(env, len);
	if (!result[0])
		return (free(result), NULL);
	result[1] = ft_strdup(split + 1);
	result[2] = NULL;
	return (result);
}

void	free_env_list(t_env *head)
{
	t_env	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
		tmp = NULL;
	}
}

void	shell_lvl_handler(t_env *head)
{
	t_env	*tmp;

	if (find_key(head, "SHLVL") == NULL)
		head = env_add_entry(head, "SHLVL=0");
	else
	{
		tmp = find_key(head, "SHLVL");
		if (ft_atoi(tmp->value) >= 1000)
			tmp->value = ft_itoa(1);
	}
}

void	update_content_of_node(t_env **created_node, char **splitted_arguments)
{
	if (!ft_strcmp((*created_node)->key, "SHLVL"))
		(*created_node)->value = ft_itoa(ft_atoi(splitted_arguments[1]) + 1);
	else
		(*created_node)->value = ft_strtrim(splitted_arguments[1], " ");
}
