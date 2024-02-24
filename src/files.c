#include "../inc/german.h"


    /*                              */
    /*      READ PRIORITY WORDS     */
    /*                              */

int     parse_priority_words( char *buf ){
    while (*buf != 0){
        if (ft_isdigit(*buf) == 0 && *buf != '\n')
        {
            return (1);
        }
        ++buf;
    }
    return (0);
}

bool    read_priority_words( int **prioritaries ){
    FILE  *file = fopen("./data/.prioritaries.txt", "r");
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
        if (*prioritaries == NULL)
        {
            write(2, "Error: read_prioritary_words(): allocation failed. (l.38)\n", 59);
            return (1);
        }
		(*prioritaries)[0] = -1;
		return (0);
	}
    *prioritaries = malloc(sizeof(int*) * (file_len + 1));
    if (*prioritaries == NULL)
	{
		write(2, "Error: read_prioritary_words(): allocation failed. (l.38)\n", 59);
		return (1);
	}
    (*prioritaries)[file_len] = -1;

    for (unsigned int i = 0; i < file_len && getline(&buf, &len, file) != -1; i++){
        if (parse_priority_words(buf)){
			printf("parse_priority_words failed\n");
			free(buf);
            free(*prioritaries);
            fclose(file);
            return (1);
        }
              
        (*prioritaries)[i] = ft_atoi(buf);
        if ((*prioritaries)[i] == -1){
            write(2, ">>> Error: read_priority_words(): ft_strdup() prioritaries allocation failed.\n", 72);
			free(buf);
            free(*prioritaries);
            fclose(file);
            return (1);
        }
    }

	free(buf);
    fclose(file);
    return (0);
}



bool    reset_prioritary_file( int *prioritaries )
{
    FILE    *file = fopen("./data/tmp", "w");
    if (file == NULL)
    {
        write(2, "Error: reset_prioritary_files(): \'tmp\' file failes to open\n", 60);
        return (1);
    }
    
    char    *tmp = NULL;
    for (size_t  i = 0; prioritaries[i] != -1; i++)
    {
        tmp = ft_itoa(prioritaries[i]);
        if (tmp == NULL
	    || fwrite(tmp, sizeof(char), strlen(tmp), file) == 0
		|| fwrite("\n", sizeof(char), 1, file) == 0)
        {
            write(2, "Error: reset_prioritary_files(): failed to write in \'tmp\' file\n", 64);
        }
		free(tmp);
    }
    if (remove("./data/.prioritaries.txt") == -1)
    {
        write(2,"Error: reset_prioritaries(): removing old prioritaries file failed.\n", 69);
        fclose(file);
        return (1);
    }
    if (rename("./data/tmp", "./data/.prioritaries.txt") == -1)
    {
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

int    error_read_dictionnary( t_data *word, size_t file_len, char **splitted_line, char *buf, FILE *file )
{
    free_tab((void **)splitted_line);
    if (buf != NULL)
        free(buf);
    free_data(file_len, word);
    fclose(file);
    return (1);
}

bool    parse_word( char **l )
{
    unsigned int i = 0;
    for (i = 0; l[i] != NULL; i++)
    {
        if (strlen(l[i]) == 0 || strlen(l[i]) > 46)
        {
            printf("word: %s\n", l[0]);
            printf("line: %s\n", l[i]);
            return (1);
        }
        unsigned int j = 0;
        for (j = 0; l[i][j] != 0; j++)
        {
            if (ft_isalpha(l[i][j]) == 0 && l[i][j] != ' ' && l[i][j] != '\'')
            {
                printf("Invalid Character\n");
                printf("word: %s\n", l[0]);
                printf("line: %s\n", l[i]);
                return (1);
            }
        }
        if(strchr(l[i], '\'') != NULL)
        {
            del_char(l[i], '\'');
        }
    }
    if (l[i] == NULL && i < 2)
    {
        printf("len error\n");
        printf("word: %s\n", l[0]);
        printf("line: %s\n", l[i]);
        return (1);
    }
    return (0);
}

bool    read_dictionnary( t_data **dico ){
    FILE  *file = fopen("./data/.dico.csv", "r");
    if (file == NULL){
        write(2, "Error: read_doctionnary(): file failed to open\n", 48);
        return (1);
    }
    
    char    **splitted_line = NULL;
    char    *buf = NULL;
    size_t  len = 0;
    const unsigned int file_len = get_file_len(file);

    if ((*dico) != NULL){
        free_data(get_len_dico((*dico)), (*dico));
    }
    (*dico) = calloc(file_len + 1, sizeof(t_data));
    if ((*dico) == NULL){
        write(2, "Error: struct (*dico): allocation failed.\n", 43);
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
            return (error_read_dictionnary((*dico), file_len, splitted_line, buf, file));
        }
        if (parse_word(splitted_line))
        {
            write(2, "Error: parse_word().\n", 22);
            return (error_read_dictionnary((*dico), file_len, splitted_line, buf, file));
        }
        (*dico)[i].to_guess = ft_strdup(splitted_line[0]);
        if ((*dico)[i].to_guess == NULL){
            write(2, "Error: setup_strings(): ft_strdup() to_guess allocation failed.\n", 65);
            return (error_read_dictionnary((*dico), file_len, splitted_line, buf, file));
        }
        (*dico)[i].answers = tabdup(splitted_line + 1);
        if ((*dico)[i].answers == NULL){
            write(2, "Error: setup_strings(): ft_strdup() answers allocation failed.\n", 64);
            return (error_read_dictionnary((*dico), file_len, splitted_line, buf, file));
        }

        if (splitted_line != NULL){
            free_tab((void **)splitted_line);
        }
    }
    (*dico)[file_len].to_guess = NULL;
    (*dico)[file_len].answers = NULL;

    free(buf);
    fclose(file);
    return (0);
}