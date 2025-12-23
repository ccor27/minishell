#include "minishell.h"

t_token_type	ft_know_type(char separator)
{
	if(separator == '|')
		return (PIPE);
	else if (separator == '<')
		return(REDIRECT_IN);
	else if(separator == '>')
		return (REDIRECT_OUT);
	else
		return(WORD);
}

int	ft_handle_quotes(char *cmd, int i,char quote)
{
	i++;
	while(cmd[i] && cmd[i]!=quote)
		i++;
	if(cmd[i]==quote)
		i++;
	return (i);
}

void	ft_parse_and_store(char *cmd, t_data *data)
{
	int i;

	i = 0;
	while (cmd[i])
	{
		if(cmd[i]==' ' || cmd[i]=='\t')
		{
			i++;
			continue;
		}
		if(is_separator(cmd[i]))
			ft_handle_separator(&i,cmd,data);
		else
			ft_handle_word(&i,cmd,data);
	}

}
void	ft_handle_word(int *i, char *cmd, t_data *data)
{
	int start;

	start = *i;
	while(cmd[*i] &&!is_separator(cmd[*i]))
		{
			if(cmd[*i]=='\''|| cmd[*i]=='\"')
				(*i) = ft_handle_quotes(cmd,*i,cmd[*i]);
			else
				(*i)++;
		}
		ft_add_token(&data->tokens, generate_token(ft_substr(cmd, start, (*i - start)),WORD));
}

void	ft_handle_separator(int *i, char *cmd, t_data *data)
{
	t_token_type token_type;
				if((cmd[*i] == '<' && cmd[*i + 1] == '<') || (cmd[*i] == '>' && cmd[*i + 1] == '>'))
			{
				if(cmd[*i] == '<')
					token_type = HERE_DOC;
				else
					token_type = APPEND;
				ft_add_token(&data->tokens,generate_token(ft_substr(cmd, *i, 2),token_type));
				(*i)+=2;
			}
			else
			{
				token_type = ft_know_type(cmd[*i]);
				if(!token_type)
					return; //TODO: handle error
				//TODO: find out which type of separator is
				ft_add_token(&data->tokens,generate_token(ft_substr(cmd, *i, 1),token_type));
				(*i)++;
			}
}
