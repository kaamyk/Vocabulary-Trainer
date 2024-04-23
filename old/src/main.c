#include "../inc/german.h"

bool	setup( t_data *data )
{
	if (read_priority_words(data))
	{
		return (1);
	}
	if (parse_dictionary(data))
	{
		free(data->prioritaries);    
		return (1);
	}
	return (0);
}

t_data	*init_data( void )
{
	t_data	*data = NULL;

	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (NULL);

	data->file = NULL;
	data->l_dico = 0;
	data->prioritaries = NULL;
	data->l_prio = 0;
	data->nb_fails = 0;
	data->nb_correct = 0;

	return (data);
}

int main( void )
{
	t_data  *data = init_data();
	if (data == NULL)
	{
		printf("Data == NULL\n");
		return (1);
	}

	srand(time(NULL));

	if (setup(data))
	{
		printf("setup failed\n");
		free(data);
		return (1);
	}
	printf(GRN "> Setup Completed.\n" COLOR_RESET);

	run(data);

	if (data->prioritaries != NULL)
		reset_prioritary_file(data->prioritaries);

	free(data->prioritaries);
	free(data);
	return (0);
}