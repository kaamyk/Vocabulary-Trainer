#include "../inc/german.h"

void	dico_correct_answer( int *good, unsigned int rank_to_del, __uint8_t *nb_correct )
{
	// Ajouter l'index devine a une liste
	unsigned int i = 0;

	while (i < MAX_LEN_INPUT && good[i] != 0){
		i++;
	}
	good[i] = rank_to_del;
	*nb_correct += 1;
}

bool	dico_wrong_answer( int **prioritaries, unsigned int *len_prio, __uint8_t *nb_fails, int rank )
{
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
	free(*prioritaries);
	*prioritaries = n_prio;
    *len_prio += 1;
    *nb_fails += 1;
	return (0);
}

bool	check_rank( int rank, int *good, int len_dico )
{
	if (rank >= len_dico)
	{
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

bool	guess_dico( int **prioritaries, unsigned int *len_prio, t_data *dico, __uint8_t *nb_fails, __uint8_t *nb_correct )
{
	printf(">>> GUESS DICO\n");
    const unsigned int    len_dico = get_len_dico(dico);
    int		rank = 0;
    char	user_input[MAX_LEN_INPUT] = {0};
	int		good[NB_CORRECT + 1] = {0}; 

    while (*nb_fails < NB_FAIL && *nb_correct < NB_CORRECT){
        rank = rand() % len_dico;
		while (check_rank(rank, good, len_dico))
		{
			rank = rand() % len_dico;
		}
        printf("Word to guess: %s\n\t", dico[rank].to_guess);
        printf("Your answer: ");

        if (fgets(user_input, MAX_LEN_INPUT, stdin) == NULL)
		{
			printf(BRED "\t>>> FALSE <<<\n" COLOR_RESET);
			printf("The word you typed is too long. (Max characters: 45)\n");
			if (dico_wrong_answer(prioritaries, len_prio, nb_fails, rank))
			{
				return (1);
			}
			printf("Right answers were:\n");
			print_tab(dico[rank].answers);
			continue ;
		}
		else if (parse_user_input(user_input))
		{
			printf(BRED "\t>>> FALSE <<<\n" COLOR_RESET);
			if (dico_wrong_answer(prioritaries, len_prio, nb_fails, rank))
			{
				return (1);
			}
			continue ;
        }
		else if (strcmp(user_input, "STOP") == 0){
			return (1);
		}

		if (check_answer(user_input, dico[rank].answers))
		{
			printf(BGRN "\t>>> CORRECT <<<\n" COLOR_RESET);
			dico_correct_answer(good, rank, nb_correct);
        }
		else
		{
			printf(BRED "\t>>> FALSE <<<\n" COLOR_RESET);
			if (dico_wrong_answer(prioritaries, len_prio, nb_fails, rank))
			{
				return (1);
			}
			for (unsigned int i = 0; dico[rank].answers[i] != NULL; i++)
			{
				printf("\t%s\n", dico[rank].answers[i]);
			}
		}
		reset_user_input(user_input);
    }
    return (0);
}