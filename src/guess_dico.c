#include "../inc/german.h"

<<<<<<< HEAD
void	dico_right_answer( int l_nb, t_data *data )
=======
void	free_dico_data( char ***tab, char **str, int **prio )
{
	if (*tab != NULL)
		free_tab((void**)*tab);
	if (*str != NULL)
	{
		free(*str);
		*str = NULL;
	}
	if (*prio != NULL)
	{
		free(*prio);
		*prio = NULL;
	}
}

void	dico_correct_answer( int *good, unsigned int rank_to_del, uint8_t *nb_correct )
>>>>>>> 7ca858be2ac805eef042a8bc86736451b9b1c618
{
	printf(BGRN "\t>>> CORRECT <<<\n" COLOR_RESET);
	data->nb_correct += 1;
	data->past_ranks[data->l_past_ranks] = l_nb;
	data->l_past_ranks += 1;
}

<<<<<<< HEAD
void	dico_wrong_answer( int l_nb, t_data *data )
{
	printf(BRED "\t>>> WRONG <<<\n" COLOR_RESET);
	data->nb_fails += 1;
	data->past_ranks[data->l_past_ranks] = l_nb;
	data->l_past_ranks += 1;
	data->priority[data->l_prio] = l_nb;
	data->l_prio += 1;
}

bool	guess_dictionary( t_data *data )
{
	bool	res = 0;
	char	*to_guess = calloc(MAX_LEN_INPUT + 1, sizeof(char));
	char	**answers = init_answers();
	if (to_guess == NULL || answers == NULL)
		return (guess_err("Error: guesspriority(): allocation failed.\n", \
		NULL, &to_guess, &answers, data));
	
	data->file = fopen("./data/dico.csv", "r");
	if (data->file == NULL)
		return (guess_err("Error: dictionnary file does not open.\n", \
		NULL, &to_guess, &answers, data));

	printf(BBLU "\n\t>>> GUESS DICO\n" COLOR_RESET);
	res = guess_loop(to_guess, answers, data, 1);

	free_all(NULL, &to_guess, &answers);
	fclose(data->file);
	return (res);
=======
bool	dico_wrong_answer( t_data *data, int rank, char **right_answers )
{
	printf(BRED "\t>>> FALSE <<<\n" COLOR_RESET);
	int	*n_prio = malloc(sizeof(int) * ((data->l_prio) + 2));
	if (n_prio == NULL)
	{
		write(2, "Error: wrong_answer(): n_prio allocation failed.\n", 50);
		return (1);
	}
	n_prio[(data->l_prio) + 1] = -1;

    if (data->prioritaries)
	{
    	unsigned int i = 0;
        while ((data->prioritaries)[i] != -1)
		{
			if ((data->prioritaries)[i] == rank)
			{
   				data->nb_fails += 1;
				free(n_prio);
				return (0);
			}
            n_prio[i] = (data->prioritaries)[i];
            i++;
        }
	    n_prio[i] = rank;
    }
    data->l_prio += 1;
    data->nb_fails += 1;
	printf("Right answers were:\n");
	print_tab(right_answers);

	free(data->prioritaries);
	data->prioritaries = n_prio;
	return (0);
}

bool	guess_dico( t_data *data )
{
    int		rank = 0;
    char	user_input[MAX_LEN_INPUT] = {0};
	int		good[NB_CORRECT + 1] = {0}; 
	char	*word_to_guess = NULL;
	char	**answers = init_tab(5);

	if (answers == NULL)
	{
		printf("Error: guess_prio(): tab initialization failed.");
		return (1);
	}
	printf(BBLU "\t>>> GUESS DICO\n" COLOR_RESET);

    while (data->nb_fails < NB_FAIL && data->nb_correct < NB_CORRECT)
	{
		define_rank_dico(&rank, good, &(data->l_dico));
		define_key_value_pair(&word_to_guess, &answers, &rank, data->file);
		
        printf("Word to guess: %s\n\t", word_to_guess);
        printf("Your answer: ");

        if (get_input(user_input))
		{
			if (dico_wrong_answer(data, rank, answers))
			{
				free_dico_data(&answers, &word_to_guess, &(data->prioritaries));
				return (1);
			}

			continue ;
		}
		else if (strcmp(user_input, "STOP") == 0)
		{
			write(2, "Stopping the session ...\n", 23);
			free_dico_data(&answers, &word_to_guess, &(data->prioritaries));
			return (1);
		}

		if (check_answer(user_input, answers))
		{
			dico_correct_answer(good, rank, &(data->nb_correct));
		}
		else if (dico_wrong_answer(data, rank, answers))
		{
			free_dico_data(&answers, &word_to_guess, &(data->prioritaries));
			return (1);
		}

		reset_user_input(user_input);
    }
	free_dico_data(&answers, &word_to_guess, &(data->prioritaries));
    return (0);
>>>>>>> 7ca858be2ac805eef042a8bc86736451b9b1c618
}