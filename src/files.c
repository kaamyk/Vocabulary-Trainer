#include "../inc/german.h"

	/*					*/
	/*	FILE UTILS		*/
	/*					*/

int	len_file( const char *file_name )
{
	int	res = 0;
	// size_t	n = 0;
	wchar_t	*buf = NULL;
	FILE	*file = fopen(file_name, "r");
	if (file == NULL)
		return (-1);
		
	while ((buf = get_next_wline(file) )!= NULL)
	{
		++res;
		free(buf);
	}
	fclose(file);
	return (res);
}

	/*					*/
	/*	PRIORITARIES	*/
	/*					*/

void	parse_priority_error( char *err_mess, wchar_t *buf, t_data *data )
{
	write(2, err_mess, strlen(err_mess));
	if (buf != NULL)
		free(buf);
	fclose(data->file);
}

bool	atoi_file( t_data *data )
{
	// size_t	n = 0;
	wchar_t	*buf = NULL;

	data->file = fopen("./data/priority.txt", "r");
	if (data->file == NULL)
		return (1);

	data->l_dico = len_file("./data/dico.csv");
	if (data->l_dico == -1)
	{
		parse_priority_error("Error: dictionary is invalid.\n", buf, data);
		return (1);
	}
	
	for (int i = 0; (buf = get_next_wline(data->file)) != NULL && i < data->l_prio; i++)
	{
		del_nl(buf);
		wprintf(L"atoi_file():buf == [%ls]\n", buf);
		if (find_first_not_of((wchar_t *)"0123456789", buf) != NULL)
		{
			parse_priority_error("Error: priority.txt contains unvalid characters.\n", buf, data);
			return (1);
		}
		data->priority[i] = (buf != NULL) ? ft_wctoi(buf) : 0;
		// printf("atoi_file(): data->priority[%d]: %d\n", i, data->priority[i]);
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
		return (1);
	return (0);
}

bool	reset_prioritary_file( t_data *data )
{
	if (data->priority == NULL)
		return (0);

	FILE    *file = fopen("./data/tmp", "w");
	if (file == NULL)
		return (error_reset(errno, data));

	wchar_t    *tmp = NULL;
	for (size_t  i = 0; data->priority[i] != -1 && data->priority[i] != 0; i++)
	{
		tmp = ft_itoa(data->priority[i]);
		if (tmp == NULL
		|| fwrite(tmp, sizeof(wchar_t), wcslen(tmp), file) == 0
		|| fwrite("\n", sizeof(wchar_t), 1, file) == 0)
		{
			write(2, "Error: reset_prioritary_files(): failed to write an element in \'tmp\' file\n", 75);
		}
		free(tmp);
	}
	if (remove("./data/priority.txt") == -1)
		return (error_reset(errno, data));
	if (rename("./data/tmp", "./data/priority.txt") == -1)
		return (error_reset(errno, data));
	fclose(file);
	return (0);
}

	/*				*/
	/*	DICTIONARY	*/
	/*				*/
bool	parse_dictionary_line( wchar_t *buf, int l_nb, t_data *data )
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