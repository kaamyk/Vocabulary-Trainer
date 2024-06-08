#include "../inc/german.h"

bool	define_guess_answers( wchar_t *to_guess, wchar_t **answers, wchar_t *buf )
{
	int i = 0;

	if (to_guess == NULL || answers == NULL || buf == NULL)
		return (1);
	
	memset(to_guess, 0, wcslen(to_guess) * sizeof(wchar_t));

	wchar_t	**splitted_line = ft_split(buf, ',');
	if (splitted_line == NULL)
		return (1);
	del_nl(splitted_line[l_tab(splitted_line) - 1]);

	memset(to_guess, 0, wcslen(to_guess) * sizeof(wchar_t));
	if (rand() % 2)
	{
		wcscpy(to_guess, splitted_line[0]);
		for (i = 0; answers[i] != NULL && answers[i][0] != 0; i++)
		{
			memset(answers[i], 0, wcslen(answers[i]) * sizeof(wchar_t));
		}
		for (i = 1; splitted_line[i] != NULL && answers[i - 1] != NULL && i < 6; i++)
		{
			wcscpy(answers[i - 1], splitted_line[i]);
		}
	}
	else
	{
		wcscpy(to_guess, splitted_line[rand() % (l_tab(splitted_line) - 1) + 1]);
		
		memset(*answers, 0, wcslen(*answers) * sizeof(wchar_t));
		wcscpy(*answers, splitted_line[0]);
		++answers;
		while(*answers != NULL && *answers[0] != 0)
		{
			memset(*answers, 0, wcslen(*answers) * sizeof(wchar_t));
			++answers;	
		}
	}
	splitted_line = ft_freetab(&splitted_line);
	return (0);
}

int	define_line( t_data *data, bool is_dico )
{
	int	res = 0;
	
	if (is_dico)
	{
		do
		{
			res = rand() % data->l_dico;
		} while (find_int_in_tab(res, data->past_ranks));
	}
	else
		res = data->priority[rand() % data->l_prio];
	//	Reset random to make it more random.
	if (res % 3 == 0)
		srand(time(NULL));	
	return (res);
}

bool	jump_to_line( wchar_t *buf, int *i, int l_nb[2], t_data *data )
{
	while (*i < l_nb[0]) // Jump to the wanted line
	{
		memset(buf, 0, BUFFER_SIZE * sizeof(wchar_t));
		if (fgetws(buf, MAX_LEN_INPUT, data->file) == NULL)
		{
			wprintf(L"Error: File reading failed.\n");
			data->err_code = errno;
			return (1);
		}
		(*i)++;
	}
	return (0);
}

bool	guess_loop( wchar_t *to_guess, wchar_t **answers, t_data *data, const bool is_dico )
{
	wchar_t	buf[BUFFER_SIZE] = {0};
	int	l_nb[2] = {0}; // [0]: actual line; [1]: previous line
	int	i = 0;
	wchar_t	*user_input = (wchar_t *)calloc(MAX_LEN_INPUT + 1, sizeof(wchar_t));
	if (errno != 0)
		return (error_loop(errno, &user_input, NULL, data));

	while (data->nb_correct < NB_CORRECT && data->nb_fails < NB_FAIL
		&& data->l_past_ranks < data->l_dico && data->l_past_ranks < NB_CORRECT + NB_FAIL)
	{
		if (!is_dico && data->l_prio <= 0)
			break ;
		l_nb[1] = l_nb[0];
		l_nb[0] =  define_line(data, is_dico);
		if (l_nb[0] < l_nb[1])
		{
			i = 0;
			fseek(data->file, 0, SEEK_SET);
		}
		else
			i = l_nb[1];

		if (jump_to_line(buf, &i, l_nb, data))
			return (error_loop(data->err_code, &user_input, NULL, data));
		if (parse_dictionary_line(buf, l_nb[0], data))
		{
			if (!is_dico || data->l_invalid_lines >= MAX_INVALID_LINE)
			{
				is_dico == 0 ? perror("Error: a priority line has a format error.\n") 
					: wprintf(RED "Information: Too many invalid lines has a format error. Stopping the session ...\n" COLOR_RESET);
				free_loop(NULL, &user_input);
				return (1);
			}
			continue ;
		}
		define_guess_answers(to_guess, answers, buf);

		wprintf(L"Word to guess: %ls\n\tYour answer: ", to_guess);

		if (get_input(user_input, answers) || check_answer(user_input, answers) == -1)
		{
			if (wcscmp(user_input, L"STOP") == 0)
			{
				wprintf(BLU "\n> Stopping the session ..." COLOR_RESET);
				free_loop(NULL, &user_input);
				return (1);
			}
			is_dico ? dico_wrong_answer(l_nb[0], answers, data) : prio_wrong_answer(answers, data);
		}
		else
			is_dico ? dico_right_answer(l_nb[0], data) : prio_right_answer(l_nb[0], data);
	}
	free_loop(NULL, &user_input);
	return (0);
}

bool	run( t_data *data )
{
	if (guess_priority(data))
		return (1);
	else if (guess_dictionary(data))
		return (1);
	print_results(data->nb_fails, data->nb_correct);
	return (0);
}