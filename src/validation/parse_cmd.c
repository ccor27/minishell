#include "minishell.h"

/**
 * make a loop through the tokens
 * calculate the size of the args
 * while the tokens' content is not a PIPE, store them in args or in the redirect
 * each time we find a PIPE, we do another cmd node
 */
