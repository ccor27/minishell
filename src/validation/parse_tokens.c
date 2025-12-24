#include "minishell.h"

/**
 * Function to know which type of token
 * the character is
 */
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

/**
 * Function to find the close quote " or '
 */
int	ft_handle_quotes(char *cmd, int i,char quote)
{
	i++;
	while(cmd[i] && cmd[i]!=quote)
		i++;
	if(cmd[i]==quote)
		i++;
	return (i);
}

/**
 * Function to parse the user's prompt in order
 * to split the data in tokens
 */
void	ft_parse_and_store(char *cmd, t_data *data)
{
	int i;

	i = 0;
	//loop to go character to character in the user's prompt
	while (cmd[i])
	{
		//skip the spaces in the start and after a space found
		if(cmd[i]==' ' || cmd[i]=='\t')
		{
			i++;
			continue;
		}
		if(is_separator(cmd[i]))
			ft_handle_separator(&i,cmd,data);//generate a token when there is a separator
		else
			ft_handle_word(&i,cmd,data);//generate a token when there is just word
	}

}

/**
 * Function to find the length the word, including
 * the cases where there are quotes
 */
void	ft_handle_word(int *i, char *cmd, t_data *data)
{
	int start;

	start = *i;
	while(cmd[*i] &&!is_separator(cmd[*i]))
		{
			//when we find a quote we'll treat within it as unique string
			if(cmd[*i]=='\''|| cmd[*i]=='\"')
				(*i) = ft_handle_quotes(cmd,*i,cmd[*i]);
			else
				(*i)++;
		}
		ft_add_token(&data->tokens, generate_token(ft_substr(cmd, start, (*i - start)),WORD));
}

/**
 * Function to handle separator in the user's prompt,
 * Basically it is to get the sparators in a token
 */
void	ft_handle_separator(int *i, char *cmd, t_data *data)
{
	t_token_type token_type;
	//to validate if we have a >> or <<
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
