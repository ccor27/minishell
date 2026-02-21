#include "minishell.h"

/**
 * Function to create a new env_node
 * in order to add it to a linked list
 */
t_env	*ft_new_env_node(char *key,char *value)
{
	t_env *new_node = malloc(sizeof(t_env));
	if(!new_node)
		return(NULL);
	new_node->key=key;
	new_node->value=value;
	new_node->next=NULL;
	return(new_node);
}

/**
 * Function to add a new node in the end of
 * the given linked list
 */
void	ft_env_add_back(t_env **head, t_env *new_node)
{
	t_env *tmp;
	if(!*head)
	{
		*head = new_node;
		return;
	}
	tmp = *head;
	while(tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
}

/**
 * Function to copy all from the env data
 * given into a linked list
 */
t_env	*ft_copy_env(char  **env)
{
	t_env	*env_list;
	char	*equals_part;
	char	*key;
	char	*value;
	int		i;

	env_list = NULL;
	i  = 0;
	while(env[i])
	{
		equals_part = ft_strchr(env[i],'=');
		if(equals_part)
		{
			key = ft_substr(env[i],0,equals_part - env[i]);
			value = ft_strdup(equals_part+1);
		}
		else
		{
			key = ft_strdup(env[i]);
			value = NULL;
		}
		ft_env_add_back(&env_list,ft_new_env_node(key,value));
		i++;
	}
	return(env_list);
}

/**
 * Helper function to know the size
 * of the env linked list
 */
int	ft_env_size(t_env *env)
{
	int count;

	count = 0;
	while(env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

/**
 * Function to conver the linked list that contains
 * the env data into a char ** in order the execv
 * function can use it
 */
char	**ft_env_to_array(t_env *env_list)
{
	int env_list_size;
	char **env_array;
	char *tmp;
	int i;

	i = 0;
	env_list_size = ft_env_size(env_list);
	env_array = malloc(sizeof(char *) * (env_list_size + 1));
	if(!env_array)
		return(NULL);
	while(env_list)
	{
		if(env_list->value)
		{
			tmp = ft_strjoin(env_list->key,"=");
			env_array[i] = ft_strjoin(tmp,env_list->value);
			free(tmp);
		}
		else
			env_array[i] = ft_strdup(env_list->key);
		env_list = env_list->next;
		i++;
	}
	env_array[i] = NULL;
	return(env_array);
}
