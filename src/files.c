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
    const unsigned int  file_len =  len_file(file);
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
		if (parse_priority_words(buf))
		{
			printf("parse_priority_words failed\n");
			free(buf);
			free(*prioritaries);
			fclose(file);
			return (1);
		}      
		(*prioritaries)[i] = ft_atoi(buf);
		if ((*prioritaries)[i] == -1)
		{
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

bool    error_parse_dictionary( char **splitted_line, char *buf, FILE *file )
{
    if (splitted_line != NULL)
        free_tab((void **)splitted_line);
    if (buf != NULL)
        free(buf);
    fclose(file);
    return (1);
}

bool    parse_word( char **l, uint8_t l_nb )
{
    unsigned int i = 0;
    for (i = 0; l[i] != NULL; i++)
    {
        if (strlen(l[i]) == 0 || strlen(l[i]) > 46)
        {
            printf("word: %s\n", l[0]);
            printf("line(%ld): %s\n", l_nb + 1, l[i]);
            return (1);
        }
        unsigned int j = 0;
        for (j = 0; l[i][j] != 0; j++)
        {
            if (l[i][j] == '\"')
            {
                printf("Invalid Character\n");
                printf("word: %s\n", l[0]);
                printf("line(%ld): %s\n", l_nb + 1, l[i]);
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
        printf("line(%ld): %s\n", l_nb, l[i]);
        return (1);
    }
    return (0);
}

bool    parse_line( char *l, size_t l_nb )
{
    for (size_t i = 0; l[i] != 0; i++)
    {
        if (l[i] == ',' && isalpha(l[i + 1]) == 0)
        {
            printf("line(%ld): %s\n", l_nb, l);
            printf("l[%ld] == %c\n", i, l[i]);
            printf("l[%ld] == %c\n", i+1, l[i+1]);
            printf("CSV format error.");
            return (1);
        }
    }
    return (0);
}

bool    parse_dictionary( void )
{
	FILE  *file = fopen("./data/.dico.csv", "r");
	if (file == NULL)
	{
		write(2, "Error: read_doctionnary(): file failed to open\n", 48);
		return (1);
	}

    char    **splitted_line = NULL;
    char    *buf = NULL;
    size_t  len = 0;
    const unsigned int file_len = len_file(file);

    for (unsigned int i = 0; i < file_len && getline(&buf, &len, file) != -1; i++)
	{
		buf[strlen(buf) - 1] = 0;
        if (parse_line(buf, i))
        {
            splitted_line = ft_split(buf, ',');
            return (error_parse_dictionary(file_len, splitted_line, buf, file));
        }
	}

	fclose(file);
	return (0);
}

char	**read_dictionary( unsigned int file_line, FILE *file )
{
	char	**splitted_line = NULL;
	char	*buf = NULL;
	size_t	len = 0;

	for (unsigned int i = 0; i < file_line && getline(&buf, &len, file) != -1; i++)
	{;}
    splitted_line = ft_split(buf, ',');
	if (splitted_line == NULL || parse_word(splitted_line, file_line))
		return (error_parse_dictionary(splitted_line, buf, file));

	free(buf);
	return (splitted_line);
}