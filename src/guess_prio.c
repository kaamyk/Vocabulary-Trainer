#include "../inc/german.h"

void	prio_wrong_answer( char **answers, t_data *data )
{
	printf(BRED "\t>>> FALSE <<<\n" COLOR_RESET);
	data->nb_fails += 1;
	printf(BCYN "Rights answers were:\n");
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
	if (errno != 0)
		return (error_guess(errno, &to_guess, NULL, data));

	char	**answers = init_answers();
	if (errno != 0)
		return (error_guess(errno, &to_guess, &answers, data));

	data->file = fopen("./data/dico.csv", "r");
	if (errno != 0)
		return (error_guess(errno, &to_guess, &answers, data));

	printf(BYEL "\n\t>>> GUESS PRIO\n" COLOR_RESET);
	res = guess_loop(to_guess, answers, data, 0);

	free_guess(&to_guess, &answers);
	fclose(data->file);
	return (res);
}