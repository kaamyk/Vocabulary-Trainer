#include "../inc/german.h"

int	print_error( int err_code )
{
	perror(strerror(err_code));
	return (err_code);
}