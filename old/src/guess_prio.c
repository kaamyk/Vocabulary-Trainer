#include "../inc/german.h"

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
	printf("prio_right_answers():\n");
    if (rank_to_del >= data->l_prio || data->prioritaries[rank_to_del] == -1)
	{
		printf("\trank_to_del: [%d]\n", rank_to_del);
		printf("\tl_prio == [%d]\n", data->l_prio);
		write(2, "Error: prio_right_answer(): rank_to_del is invalid.\n", 53);
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

void	prio_wrong_answer( uint8_t *nb_fails, char **right_answer )
{
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
		define_rank_prio(&rank_dico, data); // Assign to rank_dico the rank (from 0) to run in the dico.csv file
		define_key_value_pair(&word_to_guess, &answers, &rank_dico, data->file); // Allocate
		if (word_to_guess == NULL || answers == NULL)
		{
			free_prio_data(&answers, &word_to_guess);
			return (1);
		}
		
        printf("Word to guess: %s\n", word_to_guess);
        printf("\tYour answer: ");

		if (get_input(user_input))
		{
			prio_wrong_answer(&(data->nb_fails), answers);
			continue ;
		}
		printf("Apres get_input(): user_input: [%s]\n", user_input);
		if (strcmp(user_input, "STOP") == 0)
		{
			printf("Stopping the session.\n");
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
		free_tab((void **) answers);
		free(word_to_guess);
		reset_user_input(user_input);
    }
	free_prio_data(&answers, &word_to_guess);
    return (0);
}