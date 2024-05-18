#include "../inc/german.h"

bool	define_guess_answers( wchar_t *to_guess, wchar_t **answers, wchar_t *buf )
{
	if (to_guess == NULL || answers == NULL || buf == NULL)
		return (1);
	
	// wchar_t	*s_tmp = NULL;
	bzero(to_guess, wcslen(to_guess));

	wchar_t	**splitted_line = ft_split(buf, ',');
	if (splitted_line == NULL)
		return (1);

	bzero(to_guess, wcslen(to_guess));
	if (rand() % 2)
	{
		wcscpy(to_guess, splitted_line[0]);
		for (int i = 0; answers[i] != NULL && answers[i][0] != 0; i++)
		{
			bzero(answers[i], wcslen(answers[i]));
		}
		for (int i = 1; splitted_line[i] != NULL && answers[i] != NULL && i < 6; i++)
		{
			wcscpy(answers[i - 1], splitted_line[i]);
			del_nl(answers[i - 1]);
		}
	}
	else
	{
		wcscpy(to_guess, splitted_line[rand() % (l_tab(splitted_line) - 1) + 1]);
		del_nl(to_guess);
		
		bzero(*answers, wcslen(*answers));
		wcscpy(*answers, splitted_line[0]);
		del_nl(*answers);
		// s_tmp = *answers;
		++answers;
		while(*answers != NULL && *answers[0] != 0)
		{
			bzero(*answers, wcslen(*answers));
			++answers;	
		}
	}
	// printf("to_guess: [%ls]\n", to_guess);
	// printf("answers[0]: [%ls]\n", s_tmp);
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

bool	jump_to_line( int *i, int l_nb[2], t_data *data )
{
	while (*i < l_nb[0]) // Jump to the wanted line
	{
		if (get_next_wline(data->file) == NULL)
		{
			// printf("Error: File reading failed.\n");
			data->err_code = errno;
			return (1);
		}
		(*i)++;
	}
	return (0);
}

bool	guess_loop( wchar_t *to_guess, wchar_t **answers, t_data *data, const bool is_dico )
{
	// printf(">> guess_loop() << \n");
	wchar_t	*buf = NULL;
	// size_t	n = 0;
	int	l_nb[2] = {0}; // [0]: actual line; [1]: previous line
	int	i = 0;
	// wchar_t	user_input[MAX_LEN_INPUT + 1] = {0};
	wchar_t	*user_input = (wchar_t *)calloc(MAX_LEN_INPUT + 1, sizeof(wchar_t));
	if (errno != 0)
		return (error_loop(errno, &user_input, &buf, data));

	while (data->nb_correct < NB_CORRECT && data->nb_fails < NB_FAIL \
		&& data->l_past_ranks < data->l_dico && data->l_past_ranks < NB_CORRECT + NB_FAIL )
	{
		if (!is_dico && data->l_prio <= 0)
			break ;
		//	Setup the word to guess and the answers
		l_nb[1] = l_nb[0];
		l_nb[0] =  define_line(data, is_dico);
		if (l_nb[0] < l_nb[1])
		{
			i = 0;
			fseek(data->file, 0, SEEK_SET);
		}
		else
		{
			i = l_nb[1];
		}
		if (jump_to_line(&i, l_nb, data))
			return (error_loop(data->err_code, &user_input, &buf, data));
		if (parse_dictionary_line(buf, l_nb[0], data))
		{
			if (!is_dico)
			{
				perror("Error: a priority line has a format error.\n");
				free_loop(&buf, &user_input);
				return (1);
			}
			if (data->l_invalid_lines >= MAX_INVALID_LINE)
			{
				printf(RED "Information: Too many invalid lines has a format error. Stopping the session ...\n" COLOR_RESET);
				free_loop(&buf, &user_input);
				return (1);
			}
			continue ;
		}
		define_guess_answers(to_guess, answers, buf);

		//	User guess the answer
		//	Then parse input and checking if try is Right or Wrong
		printf("Word to guess: %ls\n\tYour answer: ", to_guess);

		if (get_input(user_input) || check_answer(user_input, answers) == 0)
		{
			if (wcscmp(user_input, (wchar_t *)"STOP") == 0)
			{
				printf(BLU "\n> Stopping the session ..." COLOR_RESET);
				free_loop(&buf, &user_input);
				return (1);
			}

			if (is_dico)
				dico_wrong_answer(l_nb[0], answers, data);
			else
				prio_wrong_answer(answers, data);
		}
		else
		{
			if (is_dico)
				dico_right_answer(l_nb[0], data);
			else
				prio_right_answer(l_nb[0], data);
		}
		//	Adding the line to the already seen
		data->past_ranks[data->l_past_ranks] = l_nb[0];
		// printf("last past rank == %d\n", data->past_ranks[data->l_past_ranks]);
		data->l_past_ranks += 1;
	}
	free_loop(&buf, &user_input);
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