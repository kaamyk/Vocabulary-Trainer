#include "../inc/german.h"

void	reset_user_input( char *user_input )
{
    for (__uint8_t i = 0; user_input[i] && i < MAX_LEN_INPUT; i++)
	{
        user_input[i] = 0;
    }
}

bool   	parse_user_input( char* user_input )
{
    const __uint8_t  len = strlen(user_input);
	__uint8_t i = 0;
    for (i = 0; i < len && user_input[i] != 0 && user_input[i] != '\n'; i++)
	{
        if (ft_isalpha(user_input[i]) == 0 && user_input[i] != ' ')
		{
			write(1, "Your answer contains unvalid characters. (Valid characters => [a, z] and [A, Z])\n", 82);
            return (1);
        }
    }

	if (i < 2)
	{
		write(1, "Error: Your answer can not be empty.\n", 38);
		return (1);
	}
	else if (user_input[i] == '\n')
	{
		user_input[i] = 0;
	}
    return (0);
}

bool    check_answer( char* user_input, char **answers )
{
    for (__uint8_t i = 0; answers[i] != NULL; i++)
	{
		printf("user_input == %s | answers[%d] == %s\n", user_input, i, answers[i]);
        if (strcmp(user_input, answers[i]) == 0)
		{
            return (1);
        }
    }
    return (0);
}

void    run( int **prioritaries, t_data *dico )
{
    const unsigned int    len_dico = get_len_dico(dico);
	if (len_dico < 2)
	{
		write(2, "Information: The dictionnary seems empty or having a single element.\n", 70);
		write(2, "> Leaving program.\n", 20);
		return ;
	}

	__uint8_t       nb_fails = 0;
    __uint8_t       nb_correct = 0;
    unsigned int    len_prioritaries = get_len_prioritaries(*prioritaries);

	if (len_prioritaries > 0 && guess_prio(prioritaries, dico, &len_prioritaries, &nb_fails, &nb_correct))
	{
		// Handle Memory
		return ;
	}
	write(2, "ici\n", 4);
	if (nb_fails < NB_FAIL && nb_correct < NB_CORRECT && guess_dico(prioritaries, &len_prioritaries, dico, &nb_fails, &nb_correct))
	{
		// Handle Memory
		return ;
	}
}