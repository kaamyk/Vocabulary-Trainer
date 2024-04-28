#include "../inc/german.h"


    /*                              */
    /*      READ PRIORITY WORDS     */
    /*                              */

bool	error_prio( const char *err_mess, FILE *file, int *prioritaries )
{
	write(2, err_mess, strlen(err_mess));
	if (file != NULL)
		fclose(file);
	if (prioritaries != NULL)
		free(prioritaries);
	return (1);
}

int     parse_priority_words( char *buf )
{
    while (*buf != 0){
        if (ft_isdigit(*buf) == 0 && *buf != '\n')
        {
            return (1);
        }
        ++buf;
    }
    return (0);
}

bool    read_priority_words( t_data *data )
{
	data->file = fopen("./data/priority.txt", "r");
	if (data->file == NULL)
	{
		write(2, "Error: read_priority_words(): file failed to open.\n", 52);
		return (error_prio("Error: read_priority_words(): file failed to open.\n", data->file, data->prioritaries));
	}

	if ((data->prioritaries) != NULL)
		free((data->prioritaries));

	const int  file_len =  len_file(data->file);
	if (file_len == -1)
		return (1);
	if (file_len == 0)
	{
		data->prioritaries = malloc(sizeof(int*) * 1);
		if (data->prioritaries == NULL)
		{
			return (error_prio("Error: read_prioritary_words(): allocation failed. (l.38)\n", data->file, data->prioritaries));
		}
		(data->prioritaries)[0] = -1;
		fclose(data->file);
		return (0);
	}
	data->prioritaries = malloc(sizeof(int*) * (file_len + 1));
	if (data->prioritaries == NULL)
	{
		fclose(data->file);
		return (error_prio("Error: read_prioritary_words(): allocation failed. (l.38)\n", data->file, data->prioritaries));
	}
	(data->prioritaries)[file_len] = -1;

	char    *buf = NULL;
	size_t  len = 0;

	for (int i = 0; i < file_len && getline(&buf, &len, data->file) != -1; i++){
		if (parse_priority_words(buf))
		{
			free(buf);
			return (error_prio("parse_priority_words failed\n", data->file, data->prioritaries));
		}      
		(data->prioritaries)[i] = ft_atoi(buf);
		if ((data->prioritaries)[i] == -1)
		{
			free(buf);
			return (error_prio("Error: read_priority_words(): ft_strdup() prioritaries allocation failed.\n", data->file, data->prioritaries));
		}
	}

	free(buf);
	fclose(data->file);
	return (0);
}

bool	reset_prioritary_file( int *prioritaries )
{
	if (prioritaries == NULL)
		return (0);

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
	if (remove("./data/priority.txt") == -1)
	{
		write(2,"Error: reset_prioritaries(): removing old prioritaries file failed.\n", 69);
		fclose(file);
		return (1);
	}
	if (rename("./data/tmp", "./data/priority.txt") == -1)
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

bool    error_parse_dictionary( char ***splitted_line, char **buf, FILE *file )
{
    if (*splitted_line != NULL)
        free_tab((void **)*splitted_line);
    if (*buf != NULL)
        free(*buf);
    fclose(file);
    return (1);
}

bool	parse_word( char **l, int l_nb )
{
    unsigned int i = 0;
    for (i = 0; l[i] != NULL; i++)
    {
        if (strlen(l[i]) == 0 || strlen(l[i]) > 46)
        {
            printf("word: %s\n", l[0]);
            printf("line(%d): %s\n", l_nb + 1, l[i]);
            return (1);
        }
        unsigned int j = 0;
        for (j = 0; l[i][j] != 0; j++)
        {
            if (l[i][j] == '\"')
            {
                printf("Invalid Character\n");
                printf("word: %s\n", l[0]);
                printf("line(%d): %s\n", l_nb + 1, l[i]);
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
        printf("line(%d): %s\n", l_nb, l[i]);
        return (1);
    }
    return (0);
}

bool	parse_line( char *l, int l_nb )
{
    for (int i = 0; l[i] != 0; i++)
    {
        if (l[i] == ',' && isalpha(l[i + 1]) == 0)
        {
            printf("parse_dictionary()): CSV format error.\n");
            printf("line(%d): %s\n", l_nb+1, l);
            printf("l[%d] == %c\n", i, l[i]);
            printf("l[%d] == %c\n", i+1, l[i+1]);
            return (1);
        }
    }
    return (0);
}

bool    parse_dictionary( t_data *data )
{
    char    *buf = NULL;
    size_t  *len = NULL;
    int file_len = 0;

	data->file = fopen("./data/dico.csv", "r");
	if (data->file == NULL)
	{
		write(2, "Error: read_doctionnary(): file failed to open\n", 48);
		return (1);
	}
	file_len = len_file(data->file);
	if (file_len == -1)
		return (1);

    for (int i = 0; i < file_len && getline(&buf, len, data->file) != -1; i++)
	{
		buf[strlen(buf) - 1] = 0;
        if (parse_line(buf, i))
        {
			free(len);
            return (error_parse_dictionary(NULL, &buf, data->file));
        }
	}
	free(len);
    data->l_dico = file_len;
	fclose(data->file);
	return (0);
}

char	**read_dictionary( unsigned int file_line, FILE *file )
{
	char	**splitted_line = NULL;
	char	*buf = NULL;
	size_t	len = 0;

    if (file == NULL)
    {
        return (NULL);
    }

	for (unsigned int i = 0; i < file_line && getline(&buf, &len, file) != -1; i++)
	{;}

    char    *nl = buf != NULL ? strchr(buf, '\n') : NULL;
    if (nl != NULL)
        *nl = 0;

    splitted_line = ft_split(buf, ',');
	if (splitted_line == NULL || parse_word(splitted_line, file_line))
    {
		error_parse_dictionary(&splitted_line, &buf, file);
        return (NULL);
    }

	free(buf);
	return (splitted_line);
}