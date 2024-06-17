#include "../inc/german.h"

	/*		PRINT		*/

void	print_tab( wchar_t **t )
{
	for (wchar_t **ptr = t; ptr != NULL && *ptr != NULL && **ptr != 0; ptr++)
	{
		wprintf(L"[%ls]\n", *ptr);
	}
}

void	print_int_tab( int *t )
{
	for (int *ptr = t; ptr != NULL && *ptr != -1  && *ptr != 0; ptr++)
	{
		wprintf(L"%d\n", *ptr);
	}
}

void	print_results( int nb_fails, int nb_correct )
{
	wprintf(L"\tEND OF SESSION !\n");
	wprintf(WHT "\n\tRight answers: " reset);
	wprintf(BGRN "%d" reset, nb_correct);
	wprintf(WHT "\tWrong answers: " reset);
	wprintf(BRED "%d\n" reset, nb_fails);
}

	/*		LENGTH		*/

int	l_tab( wchar_t **t )
{
	wchar_t	**tmp = t;

	while (*tmp != NULL)
		++tmp;
	return (tmp - t);
}

int	len_file( const char *file_name )
{
	int	res = 0;
	// size_t	n = 0;
	wchar_t	buf[BUFFER_SIZE] = {0};
	FILE	*file = fopen(file_name, "r");
	if (file == NULL)
		return (-1);
		
	// while (fgetws(buf, BUFFER_SIZE * sizeof(wchar_t), file) != NULL)
	while (fgetws(buf, BUFFER_SIZE, file) != NULL)
	{
		if (wcschr(buf, '\n') != NULL)
			++res;
	}
	perror(strerror(errno));
	fclose(file);
	return (res);
}

	/*	MODIFY VALUES	*/

void	del_nl( wchar_t *s )
{
	if (s == NULL)
		return ;
	wchar_t	*tmp = wcschr(s, L'\n');
	if (tmp != NULL)
		*tmp = L'\0';
}

wchar_t	**init_answers( void )
{
	wchar_t	**res = (wchar_t **)calloc(LEN_ANSWERS + 1, sizeof(wchar_t *));
	if (res == NULL)
		return (NULL);
	res[LEN_ANSWERS] = NULL;
	for (int i = 0; i < LEN_ANSWERS && res != NULL; i++)
	{
		res[i] = (wchar_t *)calloc(MAX_LEN_INPUT + 1, sizeof(wchar_t));
		if (res[i] == NULL)
		{
			res = ft_freetab(&res);
			return (NULL);
		}
	}
	return (res);
}

	/*	OTHER */

bool	get_input( wchar_t *user_input, wchar_t **answers )
{
	uint8_t	retry = 0;
	int8_t	r = 0;
	
	while (retry < 2)
	{
		if (fgetws(user_input, MAX_LEN_INPUT, stdin) == NULL)
		{
			wprintf(L"Word too long. (Max: 45)\n");
			return (1) ;
		}
		del_nl(user_input);
		wprintf(L"input == [%ls]\n", user_input);
		if (wcslen(user_input) < 1)
			return (1);
		
		r = check_answer(user_input, answers);
		if (r == -1)
			return (1);
		else if (r == 0)
			return (0);
		else
		{
			retry += 1;
			if (retry == 1)
				wprintf(L"Only one char is false.\n\tYour second try: ");
		}
	}
	return (1);
}

wchar_t	*find_first_not_of( wchar_t *to_find, wchar_t *str )
{
	if (to_find == NULL || str == NULL)
		return (NULL);
	while(*str)
	{
		if (wcschr(to_find, *str) == NULL)
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

int	wcscmp_spe_wchar( wchar_t *srpl, wchar_t *sspe, wchar_t *rpl, const wchar_t sp_c )
{
	wchar_t	*tmp = rpl;
	
	while (*srpl || *sspe)
	{
		if (*srpl != *sspe)
		{
			if (*srpl == *rpl && *sspe == sp_c)
			{
				while (*srpl && *rpl)
				{
					++srpl;
					++rpl;
				}
				rpl = tmp;
				++sspe;
				continue ;
			}
			else
			{
				return (*srpl - *sspe);
			}
		}
		++srpl;
		++sspe;
	}
	return (0);
}

int8_t	check_answer( wchar_t *user_input, wchar_t **answers )
{
	int8_t	wrong_char = 0;
	wchar_t	*ptr_input = user_input;
	wchar_t	**ptr_answers =  answers;
	unsigned int i = 0;
	unsigned int j = 0;
	unsigned int k = 0;

	while (answers[k][0] != L'\0')
	{
		j = 0;
		i = 0;
		wrong_char = 0;
		while (answers[k][i] != L'\0' || user_input[j] != L'\0')		
		{
			if (answers[k][i] != user_input[j])
			{
				if (answers[k][i] == L'ß' && user_input[j] == L's' && user_input[j + 1] == L's')
				{
					j += 2;
					i += 1;
					continue ;
				}
				if (wrong_char)
					break ;
				else
					wrong_char = 1;
			}
			i++;
			j++;
		}
		if (answers[k][i] == L'\0' && user_input[j] == L'\0')
			return (wrong_char); // !wrong_char => OK else 1 wrong =>retry 

		user_input = ptr_input;
		k++;
	}
	answers = ptr_answers;
	return (-1);// no match
}