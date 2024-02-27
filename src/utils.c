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

void	free_data( const unsigned int len, t_data *data )
{
	for (unsigned int i = 0; i < len; i++)
	{
		if (data[i].to_guess != NULL){
			free(data[i].to_guess);
		}
		if (data[i].answers != NULL)
		{
			char	**ptr = data[i].answers;
			for (unsigned int j = 0; ptr[j] != NULL; j++)
			{
				free(ptr[j]);
			}
			free(ptr);
		}
	}
	free(data);
	data = NULL;
}

	/*		LENGHT		*/

unsigned int    get_file_len( FILE *file ){

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

unsigned int	get_len_dico( t_data *dico )
{
	if (dico == NULL)
	{
		printf(">>> dico is empty\n");
		return (0);
	}
	
	unsigned int l = 0;
	while (dico[l].answers != NULL && dico[l].to_guess != NULL)
	{
		l++;
	}
	return (l);
}

unsigned int	get_len_prioritaries( int *prioritaries )
{
	unsigned int l = 0;
	while (prioritaries[l] != -1)
	{
		l++;
	}
	return (l);
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