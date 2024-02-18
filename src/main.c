#include "../inc/german.h"

bool	setup( int **prioritaries, t_data **dico ){
    if (read_priority_words(prioritaries) || read_dictionnary(dico)){
        return (1);
    }
    return (0);
}


int main( void ){
    int    *prioritaries = NULL;
    t_data  *dico = NULL;
    
    srand(time(NULL));

    if (setup(&prioritaries, &dico)){
        return (1);
    }

    run(&prioritaries, dico);

    reset_prioritary_file(prioritaries);

    free(prioritaries);
    free_data(get_len_dico(dico), dico);
    return (0);
}