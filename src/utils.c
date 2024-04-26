#include "../inc/german.h"

	/*		PRINT		*/

void	print_tab( char **t )
{
	for (char **ptr = t; ptr != NULL && *ptr != NULL && **ptr != 0; ptr++)
	{
		write(1, *ptr, strlen(*ptr));
		write(1, "\n", 1);
	}
}

void	print_int_tab( int *t )
{
	for (int *ptr = t; ptr != NULL && *ptr != -1  && *ptr != 0; ptr++)
	{
		printf("%d\n", *ptr);
	}
}

void	print_results( uint8_t nb_fails, uint8_t nb_correct )
{
	printf("\tEND OF SESSION !\n");
	printf(WHT "\n\tRight answers: " reset);
	printf(BGRN "%d" reset, nb_correct);
	printf(WHT "\tWrong answers: " reset);
	printf(BRED "%d\n" reset, nb_fails);
}

	/*		LENGTH		*/

int	l_tab( char **t )
{
	char	**tmp = t;

	while (*tmp != NULL)
		++tmp;
	return (tmp - t);
}

	/*	MODIFY VALUES	*/

void	del_nl( char *s )
{
	if (s == NULL)
		return ;
	char	*tmp = strchr(s, '\n');
	// printf("tmp == %s\n", tmp);
	if (tmp != NULL)
		*tmp = 0;
}

char	**init_answers( void )
{
	char	**res = calloc(LEN_ANSWERS + 1, sizeof(char *));
	if (res == NULL)
		return (NULL);
	res[LEN_ANSWERS] = NULL;
	for (int i = 0; i < LEN_ANSWERS && res != NULL; i++)
	{
		res[i] = calloc(MAX_LEN_INPUT + 1, sizeof(char));
		if (res[i] == NULL)
		{
			res = ft_freetab(&res);
			return (NULL);
		}
	}
	return (res);
}

	/*	OTHER */

bool	get_input( char *user_input )
{
	if (fgets(user_input, MAX_LEN_INPUT, stdin) == NULL)
	{
		printf("The word you typed is too long. (Max characters: 45)\n");
		return (1) ;
	}
	del_nl(user_input);
	// printf("\tuser_input: [%s]\n", user_input);
	return (strlen(user_input) < 1 ? 1 : 0);
}

char	*find_first_not_of( char *to_find, char *str )
{
	while(*str)
	{
		if (strchr(to_find, *str) == NULL)
			return (str);
		++str;
	}
	return (NULL);
}

bool	find_int_in_tab( int n, int *t )
{
	while (*t != -1)
	{
		if (*t == n)
			return (1);
		++t;
	}
	return (0);
}

bool	check_answer( char *user_input, char **answers )
{
	// printf("check_answers():\n");
	for (uint8_t i = 0; answers[i] != NULL; i++)
	{
		if (strcmp(user_input, answers[i]) == 0)
			return (1);
	}
	return (0);
}