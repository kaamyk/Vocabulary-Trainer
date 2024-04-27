#include "../inc/german.h"

char	**ft_freetab(char ***s)
{
	if (s == NULL || s[0] == NULL)
		return (NULL);
	
	int	i = 0;
	while (s[0][i] != NULL)
	{
		free(s[0][i]);
		i++;
	}
	free(s[0]);
	return (NULL);
}

void	free_loop( char **buf, char **user_input )
{
	if (buf != NULL && *buf != NULL)
		free(*buf);
	if (user_input != NULL && *user_input != NULL)
		free(*user_input);
}		

void	free_guess( char **to_guess, char ***answers )
{
	if (to_guess != NULL && *to_guess != NULL)
		free(*to_guess);
	if (answers != NULL && *answers != NULL)
		*answers = ft_freetab(answers);
}

void	free_data( t_data **data )
{
	if (data == NULL || *data == NULL)
		return ;

	if ((*data)->priority != NULL)
	{
		free((*data)->priority);
		(*data)->priority = NULL;
	}
	if ((*data)->past_ranks != NULL)
	{
		free((*data)->past_ranks);
		(*data)->past_ranks = NULL;
	}
	if ((*data)->invalid_lines != NULL)
	{
		free((*data)->invalid_lines);
		(*data)->invalid_lines = NULL;
	}
	free(*data);
	*data = NULL;
}