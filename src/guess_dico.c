#include "../inc/german.h"

void	dico_correct_answer( int *good, unsigned int rank_to_del, __uint8_t *nb_correct )
{
	// Ajouter l'index devine a une liste
	unsigned int i = 0;

	printf(BGRN "\t>>> CORRECT <<<\n" COLOR_RESET);
	while (i < MAX_LEN_INPUT && good[i] != 0){
		i++;
	}
	good[i] = rank_to_del;
	*nb_correct += 1;
}

bool	dico_wrong_answer( int **prioritaries, unsigned int *len_prio, __uint8_t *nb_fails, int rank, char **right_answers )
{
	printf(BRED "\t>>> FALSE <<<\n" COLOR_RESET);
	int	*n_prio = malloc(sizeof(int) * ((*len_prio) + 2));
	if (n_prio == NULL)
	{
		write(2, "Error: wrong_answer(): n_prio allocation failed.\n", 50);
		return (1);
	}
	n_prio[(*len_prio) + 1] = -1;

    if (prioritaries && *prioritaries)
	{
    	unsigned int i = 0;
        while ((*prioritaries)[i] != -1)
		{
			if ((*prioritaries)[i] == rank)
			{
   				*nb_fails += 1;
				free(n_prio);
				return (0);
			}
            n_prio[i] = (*prioritaries)[i];
            i++;
        }
	    n_prio[i] = rank;
    }
    *len_prio += 1;
    *nb_fails += 1;
	printf("Right answers were:\n");
	print_tab(right_answers);

	free(*prioritaries);
	*prioritaries = n_prio;
	return (0);
}

bool	check_rank( int rank, int *good, int len_dico )
{
	if (rank >= len_)
	{
		printf("Error: prio_right_answer(): rank_to_del is invalid.");
		return (1);
	}
	for (unsigned int i = 0; i < MAX_LEN_INPUT && good[i] != 0; i++)
	{
		if (good[i] == rank)
		{
			return (1);
		}
	}
	return (0);
}

bool	guess_dico( int **prioritaries, unsigned int *len_prio, __uint8_t *nb_fails, __uint8_t *nb_correct )
{
	printf(BBLU ">>> GUESS DICO\n" COLOR_RESET);
    int		rank = 0;
    char	user_input[MAX_LEN_INPUT] = {0};
	int		good[NB_CORRECT + 1] = {0}; 
	char	*word_to_guess = NULL;
	char	**values = NULL;

    while (*nb_fails < NB_FAIL && *nb_correct < NB_CORRECT)
	{
		define_rank(&rank, l_dico, good);
		define_key_value_pair(word_to_guess, values, &rank);
		
        printf("Word to guess: %s\n\t", dico[rank].to_guess);
        printf("Your answer: ");

        if (get_input(user_input))
		{
			if (dico_wrong_answer(prioritaries, len_prio, nb_fails, rank, dico[rank].answers))
			{
				return (1);
			}
			continue ;
		}
		else if (strcmp(user_input, "STOP") == 0)
		{
			printf("Stopping the session.");
			return (1);
		}

		if (check_answer(user_input, dico[rank].answers))
		{
			dico_correct_answer(good, rank, nb_correct);
        }
		else
		{
			if (dico_wrong_answer(prioritaries, len_prio, nb_fails, rank, dico[rank].answers))
			{
				return (1);
			}
		}
		reset_user_input(user_input);
    }
    return (0);
}