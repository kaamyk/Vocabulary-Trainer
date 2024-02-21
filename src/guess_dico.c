#include "../inc/german.h"

void	dico_correct_answer( int *good, unsigned int rank_to_del )
{
	// Ajouter l'index devine a une liste
	unsigned int i = 0;

	while (i < MAX_LEN_INPUT && good[i] != 0){
		i++;
	}
	good[i] = rank_to_del;
}

bool	dico_wrong_answer( int **prioritaries, unsigned int *len_prio, __uint8_t *nb_fails, unsigned int rank )
{
	int	*n_prio = malloc(sizeof(int) * ((*len_prio) + 2));
	if (n_prio == NULL)
	{
		write(2, "Error: wrong_answer(): n_prio allocation failed.\n", 50);
		return (1);
	}
	n_prio[(*len_prio) + 1] = -1;
    if (prioritaries && *prioritaries && **prioritaries)
	{
    	unsigned int i = 0;
        while ((*prioritaries)[i] != -1)
		{
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

bool	check_rank( int rank, int *good )
{
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
        printf("rank == %d\n", rank);
		while (check_rank(rank, good))
		{
			rank = rand() % len_dico;
		}
        printf("final rank == %d\n", rank);

        printf("Word to guess: %s\n\t", dico[rank].to_guess);
        printf("Your answer: ");

        if (fgets(user_input, MAX_LEN_INPUT, stdin) == NULL)
		{
			write(1, "The word you typed is too long. (Max characters: 45)\n", 54);
			if (dico_wrong_answer(prioritaries, len_prio, nb_fails, rank))
			{
				return (1);
			}
			continue ;
		}
		else if (parse_user_input(user_input))
		{
			write(1, "Your answer contains unvalid characters. (Valid characters => [a, z] and [A, Z])\n", 82);
			if (dico_wrong_answer(prioritaries, len_prio, nb_fails, rank))
			{
				return (1);
			}
			continue ;
        }

		if (check_answer(user_input, dico[rank].answers))
		{
			write(1, ">>> CORRECT <<<\n", 17);
			dico_correct_answer(good, rank);
        }
		else
		{
			write(1, ">>> FALSE <<<\n", 15);
			if (dico_wrong_answer(prioritaries, len_prio, nb_fails, rank))
			{
				return (1);
			}
		}
		reset_user_input(user_input);
    }
    return (0);
}