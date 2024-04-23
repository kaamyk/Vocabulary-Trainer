#ifndef GERMAN
#define GERMAN

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <signal.h>
#include <ctype.h>
#include <stdint.h>

#include "color.h"

#define MAX_LEN_INPUT 46
#define NB_CORRECT 20
#define NB_FAIL 10
#define MAX_INVALID_LINE 10
#define LEN_ANSWERS 5

typedef struct  s_data
{
	FILE	*file;
	int	nb_fails;
	int	nb_correct;
	int	l_dico;
	int	*priority;
	int	l_prio;
	int	*past_ranks;
	int	l_past_ranks;
	int	*invalid_lines;
	int	l_invalid_lines;
}               t_data;

/*					*/
/*		UTILS		*/
/*					*/
	// print
void	print_tab( char **t );
void	print_int_tab( int *t );

	// free
char	**ft_freetab(char ***s);
void	free_all( char **buf, char **to_guess, char ***answers );

	// lenght
int	l_tab( char **t );

	// Allocation
char	**ft_split(char const *s, char c);
char	**init_answers( void );

	// Modify values
void	del_nl( char *s );
char	**init_answers( void );
	// Define values

	// Other
bool	get_input( char *user_input );
char	*find_first_not_of( char *to_find, char *str );
bool	find_int_in_tab( int n, int *t );
bool	check_answer( char *user_input, char **answers );


/*					*/
/*		FILES		*/
/*					*/
int	len_file( const char *file_name );
void	parse_priority_error( char *err_mess, char *buf, t_data *data );
bool	atoi_file( t_data *data );
bool	parse_priority_file( t_data *data );
bool	parse_dictionary_line( char *buf, int l_nb, t_data *data );


/*						*/
/*		GUESS DICO		*/
/*						*/
void	dico_right_answer( int l_nb, t_data *data );
void	dico_wrong_answer( int l_nb, t_data *data );
bool	guess_dictionary( t_data *data );


/*						*/
/*		GUESS PRIO		*/
/*						*/
void	prio_wrong_answer( char **answers, t_data *data );
void	prio_right_answer( int l_nb, t_data *data );
bool	guess_priority( t_data *data );

/*				*/
/*		RUN		*/
/*				*/
int	guess_err( char *err_mess, char **buf, char **to_guess, char ***answers, t_data *data);
bool	define_guess_answers( char *to_guess, char **answers, char *buf );
bool	guess_loop( char *to_guess, char **answers, t_data *data, const bool is_dico );
bool	run( t_data *data );


/*					*/
/*		MAIN		*/
/*					*/
t_data	*init_data( void );

#endif