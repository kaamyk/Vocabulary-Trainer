#include "../inc/german.h"

void	reset_user_input( char *user_input )
{
    for (uint8_t i = 0; user_input[i] && i < MAX_LEN_INPUT; i++)
        user_input[i] = 0;
}

bool   	parse_user_input( char* user_input )
{
    const uint8_t  len = strlen(user_input);
	uint8_t i = 0;

    for (i = 0; i < len && user_input[i] != 0 && user_input[i] != '\n'; i++)
	{
		if (strchr(user_input, '\'') != NULL)
			del_char(user_input, '\'');
	}
	
	if (i < 1)
		return (1);
	else if (user_input[i] == '\n')
		user_input[i] = 0;

    return (0);
}

bool    check_answer( char *user_input, char **answers )
{
	printf("check_answers():\n");
	printf("\tuser_input: [%s]\n", user_input);
    for (uint8_t i = 0; answers[i] != NULL; i++)
	{
		printf("\tanswers[%d]: [%s]\n", i, answers[i]);
        if (strcmp(user_input, answers[i]) == 0)
            return (1);
    }
    return (0);
}

bool	get_input( char *user_input )
{
	char	*nl = NULL;
	if (fgets(user_input, MAX_LEN_INPUT, stdin) == NULL)
	{
		printf("The word you typed is too long. (Max characters: 45)\n");
		return (1) ;
	}
	else if (parse_user_input(user_input))
		return (1) ;
	printf("\tuser_input: [%s]\n", user_input);
	nl = strchr(user_input, '\n');
	if (nl != NULL)
		*nl = 0;
	return (0);
}

void    run( t_data *data )
{
	uint8_t		nb_fails = 0;
    uint8_t		nb_correct = 0;

    data->l_prio = len_prioritaries(data->prioritaries);
	data->file = fopen("./data/.dico.csv", "r");

	if ( data->l_prio > 0
		&& guess_prio(data))
	{
		// Handle Memory
		print_results(nb_fails, nb_correct);
	}
	else if (nb_fails < NB_FAIL && nb_correct < NB_CORRECT
		&& guess_dico(data))
	{
		// Handle Memory
		print_results(nb_fails, nb_correct);
		fclose(data->file);
		return ;
	}
	fclose(data->file);
	print_results(nb_fails, nb_correct);
}