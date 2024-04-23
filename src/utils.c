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

<<<<<<< HEAD
	/*	FREE	*/

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
	free (s[0]);
	return (NULL);
}

void	free_all( char **buf, char **to_guess, char ***answers )
=======
	/*		LENGHT		*/

int    len_file( FILE *file ){

	if (file == NULL)
	{
		printf("len_file(): file parameter is NULL.\n");
		return (-1);
	}

    char    *buf = NULL;
    size_t  n = 0;
    int    len = 0;

    while (getline(&buf, &n, file) != -1)
	{
        ++len;
    }
    fseek(file, 0, SEEK_SET);
    free(buf);
    return (len);
}

unsigned int	len_prioritaries( int *prioritaries )
>>>>>>> 7ca858be2ac805eef042a8bc86736451b9b1c618
{
	if (buf != NULL && *buf != NULL)
		free(*buf);
	if (to_guess != NULL && *to_guess != NULL)
		free(*to_guess);
	if (answers != NULL && *answers != NULL)
		*answers = ft_freetab(answers);
}

<<<<<<< HEAD
=======
uint8_t	len_tab( char **t )
{
	uint8_t	i = 0;

	while (t[i] != NULL)
		++i;
	return (i);
}

	/*		ALLOCATION		*/
>>>>>>> 7ca858be2ac805eef042a8bc86736451b9b1c618

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
<<<<<<< HEAD
	res[LEN_ANSWERS] = NULL;
	for (int i = 0; i < LEN_ANSWERS && res != NULL; i++)
	{
		res[i] = calloc(MAX_LEN_INPUT + 1, sizeof(char));
		if (res[i] == NULL)
		{
			res = ft_freetab(&res);
			return (NULL);
=======
	}
	res[ptr - t] = NULL;
	for (unsigned int i = 0; t[i] != NULL && i < ptr - t; i++){
		res[i] = ft_strdup(t[i]);
		if (res[i] == NULL)
		{
			// error
>>>>>>> 7ca858be2ac805eef042a8bc86736451b9b1c618
		}
	}
	return (res);
}

<<<<<<< HEAD
	/*	OTHER */

bool	get_input( char *user_input )
=======
char	**init_tab( const unsigned int l )
{
	char	**tab = NULL;
	
	if (l == 0)
		return (NULL);
	else if (tab != NULL)
		free_tab((void **)tab);

	tab = malloc(sizeof(char *) * l + 1);
	if (tab == NULL)
		return (NULL);
	for (unsigned int i = 0; i < l; i++)
		tab[i] = NULL;
	return (tab);
}

	/*		MODIFY VALUES		*/

void	del_char( char *s, char c )
>>>>>>> 7ca858be2ac805eef042a8bc86736451b9b1c618
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
<<<<<<< HEAD
	return (NULL);
}

bool	find_int_in_tab( int n, int *t )
{
	while (*t != -1)
	{
		if (*t == n)
			return (1);
		++t;
=======
	return ;
}

bool	check_rank( int rank, int *good, int *l_dico )
{
	if (rank >= *l_dico)
	{
		printf("Error: prio_right_answer(): rank_to_del is invalid.");
		return (1);
	}
	for (unsigned int i = 0; i < MAX_LEN_INPUT && good[i] != 0; i++)
	{
		if (good[i] == rank)
		{
			return (1);
		}
>>>>>>> 7ca858be2ac805eef042a8bc86736451b9b1c618
	}
	return (0);
}

<<<<<<< HEAD
bool	check_answer( char *user_input, char **answers )
{
	// printf("check_answers():\n");
	for (uint8_t i = 0; answers[i] != NULL; i++)
	{
		if (strcmp(user_input, answers[i]) == 0)
			return (1);
	}
	return (0);
=======
	/*		DEFINE VALUES		*/

bool	define_rank_dico( int *rank, int *good, int *l_dico )
{
	*rank = rand() % *l_dico;
	if (*rank >= *l_dico)
		return (1);
	if (*rank % 3 == 0)
		srand(time(NULL));
	while (check_rank(*rank, good, l_dico))
	{
		*rank = rand() % *l_dico;
	}
	return (0);
}

bool	define_rank_prio( int *rank_dico, t_data *data )
{
    uint8_t	rank_prio = data->l_prio != 1 ? rand() % data->l_prio : 0;
	if (rank_prio >= data->l_prio)
		return (1);

	*rank_dico = data->prioritaries[rank_prio];
	return (0);
}

uint8_t	define_word_to_guess( char **splitted_line )
{
	bool	key_val = rand() % 2;

	if (!key_val)
		return (0);
	else
	{
		uint8_t	res = rand() % (len_tab(splitted_line) - 1);
		return (res + 1);
	}
}

void	clear_tab( char **tab )
{
	if (tab == NULL)
		return ;
	while (*tab != NULL)
	{
		free(*tab);
		++(*tab);
	}
}

void	define_key_value_pair( char **word_to_guess, char ***values, int *rank_dico, FILE *file )
{
	char	**splitted_line = read_dictionary(*rank_dico, file);
	uint8_t	r_to_guess = define_word_to_guess(splitted_line);

	(void) word_to_guess;
	*word_to_guess = strdup(splitted_line[r_to_guess]);
	if (r_to_guess == 0)
		*values = tabdup(splitted_line + 1);
	else
	{
		clear_tab(*values);
		(*values)[0] = strdup(splitted_line[0]);
	}
	free_tab((void **)splitted_line);
>>>>>>> 7ca858be2ac805eef042a8bc86736451b9b1c618
}