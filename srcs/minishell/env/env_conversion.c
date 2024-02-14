/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_conversion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:03:19 by nechaara          #+#    #+#             */
/*   Updated: 2024/02/14 21:31:39 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char	*join_env(char *s1, char *s2)
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

static  void *conversion_error_handler(char **envp, size_t count)
{
    size_t  i;

    i = 0;
    while (i < count)
        free(envp[i]);
    free(envp);
    return (NULL);
}

void    *join_key_and_value(t_env *head, char **envp, size_t index)
{
    size_t      joined_string;
    char        *temp;
    
    joined_string = ft_strlen(head->key) + ft_strlen(head->value) + 2;
    envp[index] = join_env(head->key, "=");
    if (!envp[index])
        return (conversion_error_handler(envp, index));
    temp = join_env(envp[index], head->value);
    free(envp[index]);
    envp[index] = temp;
    if (!envp[index])
        return (conversion_error_handler(envp, index));
}

char    **env_to_tab(t_env *head)
{
    size_t  index;
    char    **envp;
    int  size_of_env;

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

t_env   *tab_to_env(char **envp)
{
    t_env   *head;

    head = env_init(envp);
    ft_free_matrix(1, &envp);
    return (head);
}