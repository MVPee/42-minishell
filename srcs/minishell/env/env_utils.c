/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 14:16:17 by nechaara          #+#    #+#             */
/*   Updated: 2024/03/11 17:34:40 by nechaara         ###   ########.fr       */
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

char	*no_null_join(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = -1;
	j = 0;
	if (s1)
	{
		while (s1[++i])
			str[j++] = s1[i];
	}
	i = -1;
	if (s2)
	{
		while (s2[++i])
			str[j++] = s2[i];
	}
	str[j] = '\0';
	return (str);
}

t_env	*minimal_env(void)
{
	t_env	*head;
	char	buffer[500];
	char	*current_working_directory;

	current_working_directory = ft_strdup(getcwd(buffer, 500));
	head = NULL;
	head = env_add_entry(head, "PWD=");
	env_add_entry(head, "SHLVL=");
	write_value(&head, "PWD", current_working_directory);
	return (head);
}
