#include "../inc/german.h"

int	guess_err( char *err_mess, char **buf, char **to_guess, char ***answers, t_data *data)
{
	if (err_mess != NULL)
		write(2, err_mess, strlen(err_mess));
	free_all(buf, to_guess, answers);
	if (data != NULL && data->priority != NULL)
	{
		free(data->priority);
		data->priority = NULL;
	}
	return (1);
}

bool	define_guess_answers( char *to_guess, char **answers, char *buf )
{
	if (to_guess == NULL || answers == NULL || buf == NULL)
		return (1);
	
	char	*s_tmp = NULL;
	bzero(to_guess, strlen(to_guess));

	char	**splitted_line = ft_split(buf, ',');
	if (splitted_line == NULL)
		return (1);

	bzero(to_guess, strlen(to_guess));
	if (rand() % 2)
	{
		strcpy(to_guess, splitted_line[0]);
		for (int i = 0; answers[i] != NULL && answers[i][0] != 0; i++)
		{
			bzero(answers[i], strlen(answers[i]));
		}
		for (int i = 1; splitted_line[i] != NULL && answers[i] != NULL && i < 6; i++)
		{
			strcpy(answers[i - 1], splitted_line[i]);
			del_nl(answers[i - 1]);
		}
	}
	else
	{
		strcpy(to_guess, splitted_line[rand() % (l_tab(splitted_line) - 1) + 1]);
		del_nl(to_guess);
		
		bzero(*answers, strlen(*answers));
		strcpy(*answers, splitted_line[0]);
		del_nl(*answers);
		s_tmp = *answers;
		++answers;
		while(*answers != NULL && *answers[0] != 0)
		{
			bzero(*answers, strlen(*answers));
			++answers;	
		}
	}
	printf("to_guess: [%s]\n", to_guess);
	printf("answers[0]: [%s]\n", s_tmp);
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

bool	jump_to_line( char **buf, size_t *n, int *i, int l_nb[2], t_data *data )
{
	while (*i < l_nb[0]) // Jump to the wanted line
	{
		if (getline(buf, n, data->file) == -1)
		{
			printf("Error: File reading failed.\n");
			return (1);
		}
		(*i)++;
	}
	return (0);
}

bool	guess_loop( char *to_guess, char **answers, t_data *data, const bool is_dico )
{
	char	*buf = NULL;
	char	user_input[MAX_LEN_INPUT + 1] = {0};
	size_t	n = 0;
	int	l_nb[2] = {0}; // [0]: actual line; [1]: previous line
	int	i = 0;

	while (data->nb_correct < NB_CORRECT && data->nb_fails < NB_FAIL && data->l_past_ranks < data->l_dico )
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
		if (jump_to_line(&buf, &n, &i, l_nb, data))
		{
			free_all(&buf, NULL, NULL);
			return (1);
		}
		if (parse_dictionary_line(buf, l_nb[0], data))
		{
			if (!is_dico)
			{
				printf("Error: a priority line has a format error.\n");
				free_all(&buf, NULL, NULL);
				return (1);
			}
			if (data->l_invalid_lines >= MAX_INVALID_LINE)
			{
				printf(RED "Information: Too many invalid lines has a format error. Stopping the session ...\n" COLOR_RESET);
				free_all(&buf, NULL, NULL);
				return (1);
			}
			continue ;
		}
		define_guess_answers(to_guess, answers, buf);

		//	User guess the answer
		//	Then parse input and checking if try is Right or Wrong
		printf("Word to guess: %s\n\tYour answer: ", to_guess);

		if (get_input(user_input) || check_answer(user_input, answers) == 0)
		{
			if (strcmp(user_input, "STOP") == 0)
			{
				printf(BLU "\n> Stopping the session ..." COLOR_RESET);
				free_all(&buf, NULL, NULL);
				return (1);
			}

			if (is_dico)
				dico_wrong_answer(l_nb[0], data);
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
		printf("last past rank == %d\n", data->past_ranks[data->l_past_ranks]);
		data->l_past_ranks += 1;
	}
	free_all(&buf, NULL, NULL);
	return (0);
}

bool	run( t_data *data )
{
	if (guess_priority(data))
		return (1);
	else if (guess_dictionary(data))
		return (1);
	return (0);
}