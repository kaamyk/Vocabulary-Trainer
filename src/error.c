#include "../inc/german.h"

int	print_error( int err_code )
{
	perror(strerror(err_code));
	return (err_code);
}

bool	error_guess( int err_code, wchar_t **to_guess, wchar_t ***answers, t_data *data )
{
	data->err_code = err_code;
	perror(strerror(err_code));
	free_guess(to_guess, answers);
	return (1);
}

bool	error_loop( int err_code, wchar_t **user_input, wchar_t **buf, t_data *data )
{
	data->err_code = err_code;
	perror(strerror(err_code));
	free_loop(user_input, buf);
	return (1);
}

bool	error_reset( int err_code, t_data *data )
{
	perror(strerror(err_code));
	data->err_code = err_code;
	if (data->file != NULL)
		fclose(data->file);
	return (1);
}