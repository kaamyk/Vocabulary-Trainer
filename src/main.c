#include "../inc/german.h"
t_data	*init_data( void )
{
	t_data	*data = NULL;

	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (NULL);

	data->file = NULL;
	data->nb_fails = 0;
	data->nb_correct = 0;
	data->l_dico = 0;
	data->priority = NULL;
	data->l_prio = 0;
	data->past_ranks = calloc(NB_CORRECT + NB_FAIL + 1, sizeof(int));
	if (data->past_ranks == NULL)
	{
		free(data);
		return (NULL);
	}
	data->past_ranks[NB_CORRECT + NB_FAIL] = -1;
	data->l_past_ranks = 0;
	data->invalid_lines = calloc(MAX_INVALID_LINE + 1, sizeof(int));
	if (data->invalid_lines == NULL)
	{
		free(data->past_ranks);
		free(data);
		return (NULL);
	}
	data->invalid_lines[MAX_INVALID_LINE] = -1;
	data->l_invalid_lines = 0;
	return (data);
}

int main( void )
{
	t_data  *data = init_data();
	if (data == NULL)
	{
		printf("Data == NULL\n");
		printf(RED "> Setup Failed.\n" COLOR_RESET);
		return (1);
	}
	else if (parse_priority_file(data))
	{
		free(data);
		printf(RED "> Setup Failed.\n" COLOR_RESET);
		return (1);
	}
	srand(time(NULL));
	printf(GRN "> Setup Completed.\n" COLOR_RESET);

	run(data);

	if (data->l_invalid_lines > 0)
	{
		printf("Information: invalid lines were found in dictionary:\n");
		print_int_tab(data->invalid_lines);
	}

	free(data->priority);
	free(data->invalid_lines);
	free(data->past_ranks);
	free(data);

	printf(GRN " Good bye !\n" COLOR_RESET);
	return (0);
}