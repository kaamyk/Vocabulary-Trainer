#include "../inc/german.h"

	/*					*/
	/*	PRIORITARIES	*/
	/*					*/

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
		}
	}
	free(buf);
	fclose(data->file);
	return (0);
}

bool	parse_priority_file( t_data *data )
{
	data->l_prio = len_file("./data/priority.txt");
	if (data->l_prio == -1)
		return (1);

	// data->priority = calloc(data->l_prio + 1, sizeof(int));
	// if (data->priority == NULL)
	// 	return (1);
	data->priority[data->l_prio] = -1;
	if (atoi_file(data))
	{
		free(data->priority);
		return (1);
	}
	return (0);
}

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
}