#include "../inc/german.h"

int	print_error( int err_code )
{
	perror(strerror(err_code));
	return (err_code);
}

bool	error_guess( int err_code, char **to_guess, char ***answers, t_data *data )
{
	data->err_code = err_code;
	perror(strerror(err_code));
	free_guess(to_guess, answers);
	return (1);
}

bool	error_loop( int err_code, char **user_input, char **buf, t_data *data )
{
	data->err_code = err_code;
	perror(strerror(err_code));
	free_loop(user_input, buf);
	return (1);
}