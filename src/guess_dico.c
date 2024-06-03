#include "../inc/german.h"

void	dico_right_answer( int l_nb, t_data *data )
{
	wprintf(BGRN L"\t>>> CORRECT <<<\n" COLOR_RESET);
	data->nb_correct += 1;
	data->past_ranks[data->l_past_ranks] = l_nb;
	data->l_past_ranks += 1;
}

void	dico_wrong_answer( int l_nb, wchar_t ** answers, t_data *data )
{
	wprintf(BRED L"\t>>> FALSE <<<\n" COLOR_RESET);

	data->nb_fails += 1;
	data->past_ranks[data->l_past_ranks] = l_nb;
	data->priority[data->l_prio] = l_nb;
	data->l_prio += 1;
	data->l_past_ranks += 1;

	wprintf(BCYN L"Rights answers were:\n");
	print_tab(answers);
	wprintf(COLOR_RESET);
}

bool	guess_dictionary( t_data *data )
{
	bool	res = 0;
	wchar_t	*to_guess = (wchar_t *)calloc(MAX_LEN_INPUT + 1, sizeof(wchar_t));
	if (errno != 0)
		return (error_guess(errno, &to_guess, NULL, data));

	wchar_t	**answers = init_answers();
	if (errno != 0)
		return (error_guess(errno, &to_guess, NULL, data));

	data->file = fopen("./data/dico.csv", "r");
	if (errno != 0)
		return (error_guess(errno, &to_guess, NULL, data));

	wprintf(BBLU L"\n\t>>> GUESS DICO\n" COLOR_RESET);
	res = guess_loop(to_guess, answers, data, 1);

	free_guess(&to_guess, &answers);
	fclose(data->file);
	return (res);
}