#include "../inc/german.h"

	/*					*/
	/*	PRIORITARIES	*/
	/*					*/

<<<<<<< HEAD
int	len_file( const char *file_name )
{
	int	res = 0;
	size_t	n = 0;
	char	*buf = NULL;
	FILE	*file = fopen(file_name, "r");
	if (file == NULL)
		return (-1);
		
	while (getline(&buf, &n, file) != -1)
	{
		++res;
	}
	fclose(file);
	free(buf);
	return (res);
}

void	parse_priority_error( char *err_mess, char *buf, t_data *data )
{
	write(2, err_mess, strlen(err_mess));
	if (buf != NULL)
		free(buf);
	fclose(data->file);
}

bool	atoi_file( t_data *data )
{
	size_t	n = 0;
	char	*buf = NULL;

	data->file = fopen("./data/priority.txt", "r");
	if (data->file == NULL)
		return (1);

	data->l_dico = len_file("./data/dico.csv");
	if (data->l_dico == -1)
	{
		parse_priority_error("Error: dictionary is invalid.\n", buf, data);
		return (1);
	}
	
	for (int i = 0; getline(&buf, &n, data->file) != -1 && i < data->l_prio; i++)
	{
		del_nl(buf);
		if (find_first_not_of("0123456789", buf) != NULL)
		{
			parse_priority_error("Error: priority.txt contains unvalid characters.\n", buf, data);
			return (1);
		}
		data->priority[i] = atoi(buf);
		printf("atoi_file(): data->priority[%d]: %d\n", i, data->priority[i]);
		if (data->priority[i] > data->l_dico)
		{
			parse_priority_error("Error: priority.txt contains an invalid rank.\n", buf, data);
			return (1);
=======
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
	data->file = fopen("./data/.prioritaries.txt", "r");
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
>>>>>>> 7ca858be2ac805eef042a8bc86736451b9b1c618
		}
	}
	free(buf);
	fclose(data->file);
	return (0);
}

bool	parse_priority_file( t_data *data )
{
<<<<<<< HEAD
	data->l_prio = len_file("./data/priority.txt");
	if (data->l_prio == -1)
		return (1);

	data->priority = calloc(data->l_prio + 1, sizeof(int));
	if (data->priority == NULL)
		return (1);
	data->priority[data->l_prio] = -1;
	if (atoi_file(data))
	{
		free(data->priority);
		return (1);
=======
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

	data->file = fopen("./data/.dico.csv", "r");
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
>>>>>>> 7ca858be2ac805eef042a8bc86736451b9b1c618
	}
	free(len);
    data->l_dico = file_len;
	fclose(data->file);
	return (0);
}

<<<<<<< HEAD
	/*				*/
	/*	DICTIONARY	*/
	/*				*/
bool	parse_dictionary_line( char *buf, int l_nb, t_data *data )
{
	if (buf == NULL)
		return (0);
	else if (find_int_in_tab(l_nb, data->invalid_lines))
		return (1);
	for (unsigned int j = 0; buf[j]; j++)
	{
		if (buf[j] == ',' && isalpha(buf[j + 1]) == 0)
		{
			// write(2, "Error: dictionnary format is invalid.\n", 39);
			data->invalid_lines[data->l_invalid_lines] = l_nb;
			data->l_invalid_lines += 1;
			return (1);
		}
	}
	return (0);
=======
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
    splitted_line = ft_split(buf, ',');
	if (splitted_line == NULL || parse_word(splitted_line, file_line))
    {
		error_parse_dictionary(&splitted_line, &buf, file);
        return (NULL);
    }

	free(buf);
	return (splitted_line);
>>>>>>> 7ca858be2ac805eef042a8bc86736451b9b1c618
}