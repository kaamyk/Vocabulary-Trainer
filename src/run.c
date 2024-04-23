#include "../inc/german.h"

int	guess_err( char *err_mess, char **buf, char **to_guess, char ***answers, t_data *data)
{
<<<<<<< HEAD
	if (err_mess != NULL)
		write(2, err_mess, strlen(err_mess));
	free_all(buf, to_guess, answers);
	if (data != NULL && data->priority != NULL)
	{
		free(data->priority);
		data->priority = NULL;
	}
	return (1);
=======
    for (uint8_t i = 0; user_input[i] && i < MAX_LEN_INPUT; i++)
        user_input[i] = 0;
>>>>>>> 7ca858be2ac805eef042a8bc86736451b9b1c618
}

bool	define_guess_answers( char *to_guess, char **answers, char *buf )
{
<<<<<<< HEAD
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

bool	guess_loop( char *to_guess, char **answers, t_data *data, const bool is_dico )
{
	char	*buf = NULL;
	char	user_input[MAX_LEN_INPUT + 1] = {0};
	size_t	n = 0;
	int	l_nb = 0;

	while (data->nb_correct < NB_CORRECT && data->nb_fails < NB_FAIL)
	{
		if (!is_dico && data->l_prio <= 0)
			break ;
		//	Setup the word to guess and the answers
		fseek(data->file, 0, SEEK_SET);
		l_nb =  define_line(data, is_dico);
		for (int i = 0; i < l_nb; i++) // Jump to the line l_nb
		{
			if (getline(&buf, &n, data->file) == -1)
			{
				guess_err("Error: File reading failed.\n", \
					&buf, &to_guess, &answers, data);
				return (1);
			}
		}
		if (parse_dictionary_line(buf, l_nb, data))
		{
			if (data->l_invalid_lines >= MAX_INVALID_LINE)
			{
				printf(RED "Information: Too many invalid lines. Stopping the session ...\n" COLOR_RESET);
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
				dico_wrong_answer(l_nb, data);
			else
				prio_wrong_answer(answers, data);
		}
		else
		{
			if (is_dico)
				dico_right_answer(l_nb, data);
			else
				prio_right_answer(l_nb, data);
		}
		//	Adding the line to the already seen
		data->past_ranks[data->l_past_ranks] = l_nb;
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
=======
    const uint8_t  len = strlen(user_input);
	uint8_t i = 0;

    for (i = 0; i < len && user_input[i] != 0 && user_input[i] != '\n'; i++)
	{
		if (strchr(user_input, '\'') != NULL)
			del_char(user_input, '\'');
	}
	
	if (i < 1)
		return (1);
	else if (user_input[i] == '\n')
		user_input[i] = 0;

    return (0);
}

bool    check_answer( char* user_input, char **answers )
{
    for (uint8_t i = 0; answers[i] != NULL; i++)
	{
        if (strcmp(user_input, answers[i]) == 0)
            return (1);
    }
    return (0);
}

bool	get_input( char *user_input )
{
	if (fgets(user_input, MAX_LEN_INPUT, stdin) == NULL)
	{
		printf("The word you typed is too long. (Max characters: 45)\n");
		return (1) ;
	}
	else if (parse_user_input(user_input))
		return (1) ;
	return (0);
}

void    run( t_data *data )
{
	uint8_t		nb_fails = 0;
    uint8_t		nb_correct = 0;
    unsigned int	l_prioritaries = len_prioritaries(data->prioritaries);

	data->file = fopen("./data/.dico.csv", "r");

	if (l_prioritaries > 0
		&& guess_prio(data))
	{
		// Handle Memory
		print_results(nb_fails, nb_correct);
	}
	else if (nb_fails < NB_FAIL && nb_correct < NB_CORRECT
		&& guess_dico(data))
	{
		// Handle Memory
		print_results(nb_fails, nb_correct);
		fclose(data->file);
		return ;
	}
	fclose(data->file);
	print_results(nb_fails, nb_correct);
>>>>>>> 7ca858be2ac805eef042a8bc86736451b9b1c618
}