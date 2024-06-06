#include "../inc/german.h"

void	sig_handler( int signum )
{
	if (signum == SIGINT)
	{
		exit (1);
	}
}

void	set_signal( void )
{
	struct sigaction	sig;

	memset(&sig, 0, sizeof(sig));
	sigemptyset(&sig.sa_mask);
	sig.sa_handler = &sig_handler;

	sigaction(SIGINT, &sig, NULL);
}