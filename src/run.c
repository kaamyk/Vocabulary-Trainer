#include "../inc/german.h"

void    reset_user_input( char *user_input ){
    for (__uint8_t i = 0; user_input[i] && i < 53; i++){
        user_input[i] = 0;
    }
}

bool    parse_user_input( char* user_input ){
    const __uint8_t  len = strlen(user_input);
	__uint8_t i = 0;
    for (i = 0; i < len && (user_input[i] != 0 && user_input[i] != '\n'); i++){
        if (ft_isalpha(user_input[i]) == 0){
            return (1);
        }
    }
	if (user_input[i] == '\n'){
		user_input[i] = 0;
	}
    return (0);
}

bool    check_answer( char* user_input, char **answers ){
    for (__uint8_t i = 0; answers[i] != NULL; i++){
        if (strcmp(user_input, answers[i]) == 0){
            return (1);
        }
    }
    return (0);
}

bool    wrong_answer( __uint8_t *nb_fails, unsigned int rank, int **prioritaries, unsigned int *len_priorities ){
	int	*n_prio = malloc(sizeof(int) * ((*len_priorities) + 2));
	if (n_prio == NULL){
		write(2, "Error: wrong_answer(): n_prio allocation failed.\n", 50);
		return (1);
	}
	n_prio[(*len_priorities) + 1] = -1;
    if (prioritaries && *prioritaries && **prioritaries){
    	unsigned int i = 0;
        while ((*prioritaries)[i] != -1){
            n_prio[i] = (*prioritaries)[i];
            i++;
        }
	    n_prio[i] = rank;
    }
	free(*prioritaries);
	*prioritaries = n_prio;
    *len_priorities += 1;
    *nb_fails += 1;
	return (0);
}

void    correct_answer( __uint8_t *nb_correct, bool is_prio, int **prioritaries, unsigned int rank_to_del ){
    (*nb_correct)++;
    if (is_prio && (*prioritaries)[rank_to_del] != -1){
        unsigned int i = rank_to_del;
        while ((*prioritaries)[i + 1] != -1){
            (*prioritaries)[i] = (*prioritaries)[i + 1];
            ++i;
        }
        (*prioritaries)[i] = -1;
    }
    print_prioritaries(*prioritaries);
}

int		define_rank(bool is_prio, unsigned int len_prio, unsigned int len_dico){
	if (is_prio && len_prio != 0){
		return (rand() % len_prio);
	}
	else if (len_dico != 0){
		return (rand() % len_dico);
	}
	
	return (0);
}

void    run( int **prioritaries, t_data *dico ){
    printf("Dans run\n");
    const unsigned int    len_dico = get_len_dico(dico);
	if (len_dico < 2){
		write(2, "Information: The dictionnary seems empty or having a single element.", 69);
		write(2, "> Leaving program.", 19);
		return ;
	}

	__uint8_t       nb_fails = 0;
    __uint8_t       nb_correct = 0;
    char            user_input[46] = {0};
    int				rank = 0;
    unsigned int    len_prioritaries = get_len_prioritaries(*prioritaries);
    bool            is_prio = 0;
	
	while (nb_fails < 2 && nb_correct < 2){
        is_prio = (len_prioritaries != 0);

        rank = define_rank(is_prio, len_prioritaries, len_dico);
		
        printf("Word to guess: %s\n\t", dico[rank].to_guess);
        printf("Your answer: ");
        if (fgets(user_input, 46, stdin) == NULL){
            write(1, "The word you typed is too long. (Max characters: 45)\n", 54);
            if (wrong_answer(&nb_fails, rank, prioritaries, &len_prioritaries)){
				return ;
			}
            continue ;
        }
        else if (parse_user_input(user_input)){
            write(1, "Your answer contains unvalid characters. (Valid characters => [a, z] and [A, Z])\n", 82);
            if (wrong_answer(&nb_fails, rank, prioritaries, &len_prioritaries)){
				return ;
			}
            continue ;
        }

        if (check_answer(user_input, dico[rank].answers)){
            write(1, ">>> CORRECT <<<\n", 17);
           correct_answer(&nb_correct, is_prio, prioritaries, rank);
        }
        else{
            write(1, ">>> FALSE <<<\n", 15);
            if (wrong_answer(&nb_fails, rank, prioritaries, &len_prioritaries)){
				return ;
			}
        }
        reset_user_input(user_input);
    } 
}