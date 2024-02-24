#include "../inc/german.h"

void	prio_right_answer( __uint8_t *nb_correct, int **prioritaries, unsigned int *len_prio, unsigned int rank_to_del )
{
	printf("rank_to_del == %d | len_prio == %d | prioritaries[%d] == %d\n", rank_to_del, *len_prio, rank_to_del, (*prioritaries)[rank_to_del]);
    if (rank_to_del < *len_prio && (*prioritaries)[rank_to_del] != -1)
	{
        unsigned int i = rank_to_del;
		
		*nb_correct += 1;
        while (i + 1 < *len_prio && (*prioritaries)[i + 1] != -1)
		{
            (*prioritaries)[i] = (*prioritaries)[i + 1];
            ++i;
        }
        (*prioritaries)[i] = -1;
		*len_prio -= 1;
		printf("*len_prio == %d\n", *len_prio);
    }
}

void	prio_wrong_answer( __uint8_t *nb_fails, char **right_answer ){
	*nb_fails += 1;
	// Ecrire la bonne reponse;
	write(1, "Answers:\n", 10);
	for (unsigned int i = 0; right_answer[i] != NULL; i++)
	{
		write(1, "\t", 1);
		write(1, right_answer[i], strlen(right_answer[i]));
		write(1, "\n", 1);
	}
}

bool    guess_prio( int **prioritaries, t_data *dico, unsigned int *len_prioritaries, __uint8_t *nb_fails, __uint8_t *nb_correct )
{
	printf("\n>>> GUESS PRIO\n");
    int				rank_dico = 0;
    unsigned int	rank_prio = 0;
    char			user_input[MAX_LEN_INPUT] = {0};

    while (*nb_fails < NB_FAIL && *nb_correct < NB_CORRECT && *len_prioritaries > 0)
	{
		rank_prio = *len_prioritaries != 1 ? rand() % *len_prioritaries : 0;
		if (rank_prio >= *len_prioritaries)
		{
			return (1);
		}
        rank_dico = (*prioritaries)[rank_prio];
        printf("rank == %d\n", rank_dico);

        printf("Word to guess: %s\n\t", dico[rank_dico].to_guess);
        printf("Your answer: ");

        if (fgets(user_input, MAX_LEN_INPUT, stdin) == NULL)
		{
			write(1, "The word you typed is too long. (Max characters: 45)\n", 54);
			prio_wrong_answer(nb_fails, dico[rank_dico].answers);
			continue ;
		}
		else if (parse_user_input(user_input))
		{
			write(1, "Your answer contains unvalid characters. (Valid characters => [a, z] and [A, Z])\n", 82);
			prio_wrong_answer(nb_fails, dico[rank_dico].answers);
			continue ;
        }
		else if (strcmp(user_input, "STOP") == 0){
			return (1);
		}
		
		if (check_answer(user_input, dico[rank_dico].answers))
		{
            write(1, ">>> CORRECT <<<\n", 17);
			prio_right_answer(nb_correct, prioritaries, len_prioritaries, rank_prio);
        }
		else
		{
			write(1, ">>> FALSE <<<\n", 15);
			prio_wrong_answer(nb_fails, dico[rank_dico].answers);
		}
		reset_user_input(user_input);
    }
    return (0);
}