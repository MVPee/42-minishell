/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_conversion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:03:19 by nechaara          #+#    #+#             */
/*   Updated: 2024/03/09 15:12:17 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static size_t	get_size(t_env *head)
{
	size_t	i;

	i = 0;
	while (head)
	{
		i++;
		head = head->next;
	}
	return (i);
}

static void	*conversion_error_handler(char **envp, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
		free(envp[i]);
	free(envp);
	return (NULL);
}

void	*join_key_and_value(t_env *head, char **envp, size_t index)
{
	size_t	joined_string;
	char	*temp;

	joined_string = ft_strlen(head->key) + ft_strlen(head->value) + 2;
	envp[index] = no_null_join(head->key, "=");
	if (!envp[index])
		return (conversion_error_handler(envp, index));
	temp = no_null_join(envp[index], head->value);
	free(envp[index]);
	envp[index] = temp;
	if (!envp[index])
		return (conversion_error_handler(envp, index));
	return (NULL);
}

char	**env_to_tab(t_env *head)
{
	size_t	index;
	char	**envp;
	int		size_of_env;

	size_of_env = get_size(head);
	envp = (char **)malloc((size_of_env + 1) * sizeof(char *));
	if (!envp)
		return (NULL);
	index = 0;
	while (head)
	{
		join_key_and_value(head, envp, index);
		head = head->next;
		index++;
	}
	envp[size_of_env] = NULL;
	return (envp);
}
