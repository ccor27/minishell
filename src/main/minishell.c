#include "minishell.h"

// function to validate that the enviroment data
// is correct
// void    ft_show_env_data(t_env **head)
// {
//     t_env *tmp;
//     if(!*head)
//         printf("The linked-list env is null\n");
//     tmp = *head;
//     while (tmp)
//     {
//         printf("key = %s value = %s\n",tmp->key,tmp->value);
//         tmp = tmp->next;
//     }

// }
/**
 * Function to initialize  the data struct
 * and the first node of the linked-list
 */
void	ft_init_data_struct(t_data *data, char **envp)
{
	data->env = ft_copy_env(envp);
    //ft_show_env_data(&data->env);
	data->cmds=NULL;
	data->tokens=NULL;
}

//int main(int argc, char **argv)
int main(int argc, char **argv, char **envp)
{
	char *input;
    t_data data;
    (void)argc;//this is to avoid error for unused variables
    (void)argv;
    signal(SIGINT,handle_sigint);
    signal(SIGQUIT,SIG_IGN);//ignore
    print_header();
    ft_init_data_struct(&data,envp);
    while(1)
    {
        input = readline("minishell$> ");
        if(!input)
        {
            printf("exit\n");
            break;
        }
        if(input[0]!='\0')
        {
            add_history(input);
            ft_parse_and_store(input,&data);
            //TODO: what should we do if the are any unclose quote?
            ft_parse_cmd(data.tokens,&data);
            ft_here_doc(&data);
            ft_expanders(&data);
            //validate if there are in built commands
            //execute commands
            //ft_print_tokens(&data.tokens);
            ft_print_cmds(data.cmds);
            ft_free_data(&data);
        }
        free(input);
    }
    return (0);
}
