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

void	print_results( __uint8_t nb_fails, __uint8_t nb_correct )
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

unsigned int    len_file( FILE *file ){

    char    *buf = NULL;
    size_t  n = 0;
    unsigned int    len = 0;

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

	while ((*t)[i] != NULL)
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
		if (res[i] == NULL){
			// error
		}
	}
	return (res);
}

bool	init_tab( char **tab, const unsigned int l )
{
	if (l == 0)
		return (0);
	else if (tab != NULL)
		free_tab(tab);

	tab = malloc(sizeof(char *) * l + 1);
	if (tab == NULL)
		return (1);
	for (unsigned int i = 0; i < l; i++)
		tab[l] = NULL;
	return (0);
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

void	clear_tab( char **tab )
{
	
}

	/*		DEFINE VALUES		*/

void	define_rank_dico( unsigned int *rank, const unsigned int l_dico, int *good )
{
	*rank = rand() % l_dico;
	if (*rank % 3 == 0)
		srand(time(NULL));
	while (check_rank(*rank, good, l_dico))
	{
		*rank = rand() % l_dico;
	}
}

void	define_rank_prio( unsigned *rank_dico, unsigned int **prioritaries, uint8_t *len_prioritaries )
{
    uint8_t	rank_prio = 0;

	rank_prio = *len_prioritaries != 1 ? rand() % *len_prioritaries : 0;
	if (rank_prio >= *len_prioritaries)
	{
		return (1);
	}
	*rank_dico = (*prioritaries)[rank_prio];
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

void	define_key_value_pair( char *word_to_guess, char **values, unsigned int *rank_dico )
{
	char	**splitted_line = read_dictionary(*rank_dico, file);
	uint8_t	r_to_guess = define_word_to_guess(splitted_line);

	word_to_guess = strdup((*splitted_line)[r_to_guess]);
	if (r_to_guess == 0)
		values = tabdup(splitted_line + 1);
	else
	{
		clear_tab(values);
		values[0] = strdup((*splitted_line)[0]);
	}
}