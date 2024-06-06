#include "../inc/german.h"
t_data	*init_data( void )
{
	t_data	*data = NULL;

	data = (t_data *)malloc(sizeof(t_data));
	if (data == NULL)
		return (NULL);

	data->file = NULL;
	data->nb_fails = 0;
	data->nb_correct = 0;
	data->l_dico = 0;
	data->priority = (wchar_t *)calloc(NB_FAIL + 1, sizeof(int));
	if (data->priority == NULL)
	{
		free_data(&data);
		return (NULL);
	}
	data->priority[NB_FAIL] = -1;
	data->l_prio = 0;

	data->past_ranks = (wchar_t *)calloc(NB_CORRECT + NB_FAIL + 1, sizeof(int));
	if (data->past_ranks == NULL)
	{
		free_data(&data);
		return (NULL);
	}
	data->past_ranks[NB_CORRECT + NB_FAIL] = -1;

	data->l_past_ranks = 0;
	data->invalid_lines = (wchar_t *)calloc(MAX_INVALID_LINE + 1, sizeof(int));
	if (data->invalid_lines == NULL)
	{
		free_data(&data);
		return (NULL);
	}
	data->invalid_lines[MAX_INVALID_LINE] = -1;
	data->l_invalid_lines = 0;
	data->err_code = 0;
	return (data);
}

int main( void )
{
	int	return_value = 0;
	t_data  *data = init_data();



	if (setlocale(LC_ALL, "de_DE.UTF-8") == NULL)
	{
		perror(strerror(errno));
	}
	fwide(stdout, 1);

	set_signal();
	if (data == NULL)
		return (print_error(errno));
	else if (parse_priority_file(data))
	{
		free_data(&data);
		wprintf(RED "> Setup Failed.\n" COLOR_RESET);
		return (1);
	}
	srand(time(NULL));
	wprintf(GRN "> Setup Completed.\n" COLOR_RESET);

	run(data);

	if (data->l_invalid_lines > 0)
	{
		wprintf(L"Information: invalid lines were found in dictionary: ");
		print_int_tab(data->invalid_lines);
		wprintf(L"\n");
	}

	reset_prioritary_file(data);

	return_value = data->err_code;
	free_data(&data);

	wprintf(GRN " Good bye !\n" COLOR_RESET);
	return (return_value);
}