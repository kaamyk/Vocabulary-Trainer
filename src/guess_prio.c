#include "../inc/german.h"

void	prio_right_answer( __uint8_t *nb_correct, int **prioritaries, unsigned int *len_prio, unsigned int rank_to_del )
{
    if (rank_to_del >= *len_prio || (*prioritaries)[rank_to_del] == -1)
	{
		printf("Error: prio_right_answer(): rank_to_del is invalid.");
		return ;
	}
	printf(BGRN "\t>>> CORRECT <<<\n" COLOR_RESET);
	unsigned int i = rank_to_del;
	
	*nb_correct += 1;
	while (i + 1 < *len_prio && (*prioritaries)[i + 1] != -1)
	{
		(*prioritaries)[i] = (*prioritaries)[i + 1];
		++i;
	}
	(*prioritaries)[i] = -1;
	*len_prio -= 1;
}

void	prio_wrong_answer( __uint8_t *nb_fails, char **right_answer ){
	printf(BRED "\t>>> FALSE <<<\n" COLOR_RESET);
	*nb_fails += 1;
	printf( "Answers:\n");
	print_tab(right_answer);
}

bool    guess_prio( unsigned int **prioritaries, uint8_t *len_prioritaries, __uint8_t *nb_fails, __uint8_t *nb_correct )
{
	printf(BYEL "\n\t>>> GUESS PRIO\n" COLOR_RESET);
    unsigned int	rank_dico = 0;
    char	user_input[MAX_LEN_INPUT] = {0};
	char	*word_to_guess = NULL;
	char	**answers = NULL;
	
	init_tab(answers, 5);

    while (*nb_fails < NB_FAIL && *nb_correct < NB_CORRECT && *len_prioritaries > 0)
	{
		define_rank_prio(&rank_dico, prioritaries, len_prioritaries);
		define_key_value_pair(word_to_guess, answers, &rank_dico);

        printf("Word to guess: %s\n\t", word_to_guess);
        printf("Your answer: ");

		if (get_input(user_input))
		{
			prio_wrong_answer(nb_fails, answers);
			continue ;
		}

		if (strcmp(user_input, "STOP") == 0)
		{
			printf("Stopping the session.");
			return (1);
		}
		else if (check_answer(user_input, answers))
		{
			prio_right_answer(nb_correct, prioritaries, len_prioritaries, rank_prio);
        }
		else
		{
			prio_wrong_answer(nb_fails, answers);
		}
		reset_user_input(user_input);
    }
    return (0);
}