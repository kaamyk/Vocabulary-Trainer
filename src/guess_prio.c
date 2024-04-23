#include "../inc/german.h"

<<<<<<< HEAD
void	prio_wrong_answer( char **answers, t_data *data )
{
	printf(BRED "\t>>> FALSE <<<\n" COLOR_RESET);
	data->nb_fails += 1;
	printf(BHCYN "Answers:\n");
	print_tab(answers);
	printf(COLOR_RESET);
}

void	prio_right_answer( int l_nb, t_data *data )
{
	// printf("prio_right_anwer():\n");
	printf(BGRN "\t>>> CORRECT <<<\n" COLOR_RESET);
	uint8_t	i = 0;

	while (data->priority[i] != -1)
	{
		if (data->priority[i] == l_nb)
			break ;
		i++;
	}
	// printf("to erase: [%d] && data->l_prio:[%d]\n", data->priority[i], data->l_prio);
	while (i + 1 < data->l_prio)
	{
		data->priority[i] = data->priority[i + 1];
		++i;
	}
	data->priority[i] = 0;
	data->l_prio -= 1;
	data->nb_correct += 1;
}

bool	guess_priority( t_data *data )
{
	bool	res = 0;
	char	*to_guess = calloc(MAX_LEN_INPUT + 1, sizeof(char));
	char	**answers = init_answers();
	if (to_guess == NULL || answers == NULL)
		return (guess_err("Error: guesspriority(): allocation failed.\n", NULL, &to_guess, &answers, data));
	
	data->file = fopen("./data/dico.csv", "r");
	if (data->file == NULL)
		return (guess_err("Error: dictionnary file does not open.\n", NULL, &to_guess, &answers, data));

	printf(BYEL "\n\t>>> GUESS PRIO\n" COLOR_RESET);
	res = guess_loop(to_guess, answers, data, 0);

	free_all(NULL, &to_guess, &answers);
	fclose(data->file);
	return (res);
=======
void	free_prio_data( char ***tab, char **str )
{
	if (*tab != NULL)
		free_tab((void**)*tab);
	if (*str != NULL)
	{
		free(*str);
		*str = NULL;
	}
}

void	prio_right_answer( t_data *data, unsigned int rank_to_del )
{
    if (rank_to_del >= data->l_prio || data->prioritaries[rank_to_del] == -1)
	{
		printf("Error: prio_right_answer(): rank_to_del is invalid.");
		return ;
	}
	printf(BGRN "\t>>> CORRECT <<<\n" COLOR_RESET);
	unsigned int i = rank_to_del;
	
	data->nb_correct += 1;
	while (i + 1 < data->l_prio && (data->prioritaries)[i + 1] != -1)
	{
		(data->prioritaries)[i] = (data->prioritaries)[i + 1];
		++i;
	}
	(data->prioritaries)[i] = -1;
	data->l_prio -= 1;
}

void	prio_wrong_answer( uint8_t *nb_fails, char **right_answer ){
	printf(BRED "\t>>> FALSE <<<\n" COLOR_RESET);
	*nb_fails += 1;
	printf( "Answers:\n");
	print_tab(right_answer);
}

bool    guess_prio( t_data *data )
{
    int	rank_dico = 0;
    char	user_input[MAX_LEN_INPUT] = {0};
	char	*word_to_guess = NULL;
	char	**answers = init_tab(5);

	if (answers == NULL)
	{
		printf("Error: guess_prio(): tab initialization failed.");
		return (1);
	}
	printf(BYEL "\n\t>>> GUESS PRIO\n" COLOR_RESET);

	
    while (data->nb_fails < NB_FAIL && data->nb_correct < NB_CORRECT && data->l_prio > 0)
	{
		define_rank_prio(&rank_dico, data);
		define_key_value_pair(&word_to_guess, &answers, &rank_dico, data->file);

        printf("Word to guess: %s\n\t", word_to_guess);
        printf("Your answer: ");

		if (get_input(user_input))
		{
			prio_wrong_answer(&(data->nb_fails), answers);
			continue ;
		}
		else if (strcmp(user_input, "STOP") == 0)
		{
			printf("Stopping the session.");
			free_prio_data(&answers, &word_to_guess);
			return (1);
		}
		else if (check_answer(user_input, answers))
		{
			prio_right_answer(data, rank_dico);
        }
		else
		{
			prio_wrong_answer(&(data->nb_fails), answers);
		}
		reset_user_input(user_input);
    }
	free_prio_data(&answers, &word_to_guess);
    return (0);
>>>>>>> 7ca858be2ac805eef042a8bc86736451b9b1c618
}