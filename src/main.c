#include "../inc/german.h"

bool	setup( int **prioritaries, t_data **dico ){
    if (read_priority_words(prioritaries))
    {
        return (1);
    }
    if (parse_dictionnary(dico))
    {
        free(*prioritaries);    
        return (1);
    }
    return (0);
}


int main( void ){
    int    *prioritaries = NULL;
    t_data  *dico = NULL;
    
    srand(time(NULL));

    if (setup(&prioritaries, &dico)){
        printf("setup failed\n");
        return (1);
    }

    run(&prioritaries, dico);

    if (prioritaries != NULL)
    {
        reset_prioritary_file(prioritaries);
    }

    free(prioritaries);
    free_data(len_dico(dico), dico);
    return (0);
}