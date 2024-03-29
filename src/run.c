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
        if (ft_isalpha(user_input[i]) == 0 && user_input[i] != ' ' && user_input[i] != '\'')
		{
			printf( "Your answer contains unvalid characters. (Valid characters => [a - z], [A - Z], space, single quote )\n");
			return (1);
		}
		else if (strchr(user_input, '\'') != NULL)
		{
			del_char(user_input, '\'');
		}
	}

	if (i < 1)
	{
		printf( "Error: Your answer can not be empty.\n");
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
        if (strcmp(user_input, answers[i]) == 0)
		{
            return (1);
        }
    }
    return (0);
}

bool	get_input( char *user_input )
{
	if (fgets(user_input, MAX_LEN_INPUT, stdin) == NULL)
	{
		printf("The word you typed is too long. (Max characters: 45)\n");
		return (1) ;
	}
	else if (parse_user_input(user_input))
	{
		printf("Your answer contains unvalid characters. (Valid characters => [a, z] and [A, Z])\n");
		return (1) ;
	}
	return (0);
}

void    run( int **prioritaries, t_data *dico )
{
    const unsigned int    len_dico = get_len_dico(dico);
	if (len_dico < 2)
	{
		write(2, "Information: The dictionnary seems empty or having a single element.\n", 70);
		return ;
	}

	__uint8_t		nb_fails = 0;
    __uint8_t		nb_correct = 0;
    unsigned int	len_prioritaries = get_len_prioritaries(*prioritaries);

	if (len_prioritaries > 0
		&& guess_prio(prioritaries, &len_prioritaries, dico, &nb_fails, &nb_correct))
	{
		// Handle Memory
		print_results(nb_fails, nb_correct);
		return ;
	}
	if (nb_fails < NB_FAIL && nb_correct < NB_CORRECT
		&& guess_dico(prioritaries, &len_prioritaries, dico, &nb_fails, &nb_correct))
	{
		// Handle Memory
		print_results(nb_fails, nb_correct);
		return ;
	}
	print_results(nb_fails, nb_correct);
}