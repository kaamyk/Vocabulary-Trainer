#include "../inc/german.h"


    /*                              */
    /*      READ PRIORITY WORDS     */
    /*                              */

int     parse_priority_words( char *buf ){
    while (*buf != 0){
        if (ft_isdigit(*buf) == 0 && *buf != '\n'){
            return (1);
        }
        ++buf;
    }
    return (0);
}

bool    read_priority_words( int **prioritaries ){
    FILE  *file = fopen("./data/prioritaries.txt", "r");
    if (file == NULL){
        write(2, "Error: read_priority_words(): file failed to open.\n", 52);
        return (1);
    }

    char    *buf = NULL;
    size_t  len = 0;

    if ((*prioritaries) != NULL){
        free((*prioritaries));
    }
    const unsigned int  file_len =  get_file_len(file);
	if (file_len == 0)
	{
		*prioritaries = malloc(sizeof(int*) * 1);
		(*prioritaries)[0] = -1;
		return (0);
	}
    *prioritaries = malloc(sizeof(int*) * (file_len + 1));
    (*prioritaries)[file_len] = -1;

    for (unsigned int i = 0; i < file_len && getline(&buf, &len, file) != -1; i++){
        if (parse_priority_words(buf)){
            //error_handling function;
			printf("parse_priority_words failed\n");
			free(buf);
            free(*prioritaries);
            fclose(file);
            return (1);
        }
              
        (*prioritaries)[i] = ft_atoi(buf);
        if ((*prioritaries)[i] == -1){
            write(2, ">>> Error: read_priority_words(): ft_strdup() prioritaries allocation failed.\n", 72);
            //error_handling function;
			free(buf);
            free(*prioritaries);
            fclose(file);
            return (1);
        }
        printf("prioritaries[%d] = [%d]\n", i, (*prioritaries)[i]);
    }

	free(buf);
    fclose(file);
    return (0);
}



bool    reset_prioritary_file( int *prioritaries ){
    FILE    *file = fopen("./data/tmp", "w");
    if (file == NULL){
        write(2, "Error: reset_prioritary_files(): \'tmp\' file failes to open\n", 60);
        return (1);
    }
    
    char    *tmp = NULL;
    for (size_t  i = 0; prioritaries[i] != -1; i++){
        tmp = ft_itoa(prioritaries[i]);
        if (tmp == NULL
			|| fwrite(tmp, sizeof(char), strlen(tmp), file) == 0
			|| fwrite("\n", sizeof(char), 1, file) == 0){
            write(2, "Error: reset_prioritary_files(): failed to wirte in \'tmp\' file\n", 64);
        }
		free(tmp);
    }
    if (remove("./data/prioritaries.txt") == -1){
        write(2,"Error: reset_prioritaries(): removing old prioritaries file failed.\n", 69);
        fclose(file);
        return (1);
    }
    if (rename("./data/tmp", "./data/prioritaries.txt") == -1){
        write(2,"Error: reset_prioritaries(): renaming of tmp file failed.\n", 59);
        fclose(file);
        return (1);
    }
    fclose(file);
    return (0);
}

    /*                      */
    /*      READ DICO       */
    /*                      */

void    error_read_dictionnary( t_data *word, size_t file_len, char **splitted_line, char *buf ){
    free_tab((void **)splitted_line);
    if (buf != NULL)
        free(buf);
    free_data(file_len, word);
}

bool    read_dictionnary( t_data **dico ){
    FILE  *file = fopen("./data/words.csv", "r");
    if (file == NULL){
        write(2, ">>> Error: read_doctionnary(): file failed to open\n", 31);
        return (1);
    }
    
    char    **splitted_line = NULL;
    char    *buf = NULL;
    size_t  len = 0;
    const unsigned int file_len = get_file_len(file);

    if ((*dico) != NULL){
        free_data(get_len_dico((*dico)), (*dico));
    }
    (*dico) = malloc(sizeof(t_data) * (file_len + 1));
    if ((*dico) == NULL){
        write(2, "Error: struct (*dico): allocation failed.\n", 40);
        fclose(file);
        return (0);
    }

    for (unsigned int i = 0; i < file_len && getline(&buf, &len, file) != -1; i++){
        if (strchr(buf, '\n')){
            buf[strlen(buf) - 1] = 0;
        }
        splitted_line = ft_split(buf, ',');
        if (splitted_line == NULL){
            //error
            write(2, "Error: setup_strings(): ft_split failed.\n", 42);
            error_read_dictionnary((*dico), file_len, splitted_line, buf);
            fclose(file);
            return (1);
        }
        //  parse_line();
        (*dico)[i].to_guess = ft_strdup(splitted_line[0]);
        if ((*dico)[i].to_guess == NULL){
            write(2, ">>> Error: setup_strings(): ft_strdup() to_guess allocation failed.\n", 57);
            error_read_dictionnary((*dico), file_len, splitted_line, buf);
            fclose(file);
            return (1);
        }
        (*dico)[i].answers = tabdup(splitted_line + 1);
        if ((*dico)[i].answers == NULL){
            write(2, ">>> Error: setup_strings(): ft_strdup() answers allocation failed.\n", 57);
            error_read_dictionnary((*dico), file_len, splitted_line, buf);
            fclose(file);
            return (1);
        }

        if (splitted_line != NULL){
            free_tab((void **)splitted_line);
        }
        printf("The german dico to guess is : [%s].\n", (*dico)[i].to_guess);
        printf("answers:\n");
        print_tab((*dico)[i].answers);

    }
    (*dico)[file_len].to_guess = NULL;
    (*dico)[file_len].answers = NULL;

    free(buf);
    fclose(file);
    return (0);
}