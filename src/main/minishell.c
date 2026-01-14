#include "minishell.h"

/* function to validate that the enviroment data
is correct
void    ft_show_env_data(char **envp)
{
    int i = 0;

    while (envp[i] != NULL)
    {
        printf("%s\n", envp[i]);
        i++;
    }
}*/
/**
 * Function to initialize  the data struct
 * and the first node of the linked-list
 */
void	ft_init_data_struct(t_data *data, char **envp)
{
	data->env = envp;
    //ft_show_env_data(envp);
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
            //
            //printf("The prompt received is: %s\n",input);
            ft_parse_and_store(input,&data);
            ft_print_tokens(&data.tokens);
        }
        free(input);
    }
    return (0);
}
