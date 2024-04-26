#include "../inc/german.h"

void	dico_right_answer( int l_nb, t_data *data )
{
	printf(BGRN "\t>>> CORRECT <<<\n" COLOR_RESET);
	data->nb_correct += 1;
	data->past_ranks[data->l_past_ranks] = l_nb;
	data->l_past_ranks += 1;
}

void	dico_wrong_answer( int l_nb, t_data *data )
{
	printf(BRED "\t>>> FALSE <<<\n" COLOR_RESET);
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

	free_loop(NULL, &to_guess, &answers);
	fclose(data->file);
	return (res);
}