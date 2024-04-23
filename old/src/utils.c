#include "../inc/german.h"

	/*		PRINTING		*/

void	print_tab( char **t )
{
	for (char **ptr = t; ptr != NULL && *ptr != NULL; ptr++)
	{
		printf("%s\n", *ptr);
	}
}

void	print_prioritaries( int *p )
{
	for (unsigned int i = 0; p[i] != -1; i++)
	{
		printf("prio[%d] = %d\n", i, p[i]);
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

	/*		FREE		*/

void	free_tab( void **t )
{
	for (unsigned int i = 0; t[i]; i++)
	{
		free(t[i]);
	}
	free(t);
	t = NULL;
}

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
{
	unsigned int l = 0;
	while (prioritaries[l] != -1)
	{
		l++;
	}
	return (l);
}

uint8_t	len_tab( char **t )
{
	uint8_t	i = 0;

	while (t[i] != NULL)
		++i;
	return (i);
}

	/*		ALLOCATION		*/

char	**tabdup( char **t )
{
	char	**res = NULL;

	if (t == NULL)
	{
		write(2, "Error: duptab(): no input tab.\n", 32);
		return (NULL);
	}
	char	**ptr = t;
	while (*ptr != NULL)
	{
		ptr++;
	}
	res = malloc(sizeof(char *) * (ptr - t + 1));
	if (res == NULL)
	{
		write(2, "Error: read_file()->duptab(): res allocation failed.\n", 54);
		return (NULL);
	}
	res[ptr - t] = NULL;
	for (unsigned int i = 0; t[i] != NULL && i < ptr - t; i++){
		res[i] = ft_strdup(t[i]);
		if (res[i] == NULL)
		{
			// error
		}
	}
	return (res);
}

char	**init_tab( const unsigned int l )
{
	char	**tab = NULL;
	
	if (l == 0)
		return (NULL);
	else if (tab != NULL)
		free_tab((void **)tab);

	tab = malloc(sizeof(char *) * (l + 1));
	if (tab == NULL)
		return (NULL);
	for (unsigned int i = 0; i <= l; i++)
		tab[i] = NULL;
	return (tab);
}

	/*		MODIFY VALUES		*/

void	del_char( char *s, char c )
{
	unsigned int j = 0;
	if (c == 0 || s == NULL)
	{
		return ;
	}
	for (unsigned int i = 0; s[i] != 0; i++)
	{
		if (s[i] == c)
		{
			j = i + 1;
			while (s[j] != 0)
			{
				s[j - 1] = s[j];
				++j;
			}
			s[j - 1] = 0;
		}
	}
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
	}
	return (0);
}

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

	*rank_dico = data->prioritaries[rank_prio] - 1;
	return (0);
}

int8_t	define_word_to_guess( char **splitted_line )
{
	if (splitted_line == NULL)
		return (-1);
	
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
		printf("*tab == [%s]\n", *tab);
		free(*tab);
		++tab;
	}
}

void	define_key_value_pair( char **word_to_guess, char ***values, int *rank_dico, FILE *file )
{
	char	**splitted_line = read_dictionary(*rank_dico, file);
	int8_t	r_to_guess = define_word_to_guess(splitted_line);

	if (r_to_guess == -1)
		return ;
	(void) word_to_guess;
	*word_to_guess = strdup(splitted_line[r_to_guess]);
	if (*word_to_guess == NULL)
	{
		write(2, "Error: define_key_value_pair(): strdup() allocation error.", 59);
		return ;
	}
	if (r_to_guess == 0)
		*values = tabdup(splitted_line + 1);
	else
	{
		clear_tab(*values);
		(*values)[0] = strdup(splitted_line[0]);
	}
	free_tab((void **)splitted_line);
}