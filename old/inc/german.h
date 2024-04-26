#ifndef GERMAN
#define GERMAN

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <signal.h>
#include <ctype.h>

#include "../libft/libft.h"
#include "color.h"

#define MAX_LEN_INPUT 46
#define NB_CORRECT 20
#define NB_FAIL 10

typedef struct  s_data
{
	FILE	*file;
	int	l_dico;
	int	*prioritaries;
	uint8_t	l_prio;
	uint8_t	nb_fails;
	uint8_t	nb_correct;
}               t_data;

/*					*/
/*		UTILS		*/
/*					*/
	/* print */
void	print_tab( char **t );
void	print_prioritaries( int *p );
void	print_results( uint8_t nb_fails, uint8_t nb_correct );
	/* free */
void	free_tab( void **t );
	/* lenght */
int	len_file( FILE *file );
unsigned int	len_prioritaries( int *prioritaries );
uint8_t	len_tab( char **t );
	/* Allocation */
char	**tabdup( char **t );
char	**init_tab( const unsigned int l );
	/* Modify values */
void	del_char( char *s, char c );
bool	check_rank( int rank, int *good, int *l_dico );
void	clear_tab( char **tab );
	/* Define values */
bool	define_rank_dico( int *rank, int *good, int *l_dico );	
bool	define_rank_prio( int *rank_dico, t_data *data );
int8_t	define_word_to_guess( char **splitted_line );
void    define_key_value_pair( char **key, char ***values, int *rank_dico, FILE *file );


/*					*/
/*		FILES		*/
/*					*/
bool	error_prio( const char *err_mess, FILE *file, int *prioritaries );
int		parse_priority_words( char *buf );
bool	read_priority_words( t_data *data );
bool	reset_prioritary_file( int *prioritaries );
bool    error_parse_dictionary( char ***splitted_line, char **buf, FILE *file );
bool	parse_word( char **l, int l_nb );
bool	parse_line( char *l, int l_nb );
bool	parse_dictionary( t_data *data );
char	**read_dictionary( unsigned int file_line, FILE *file );


/*				*/
/*		RUN		*/
/*				*/
bool	parse_user_input( char* user_input );
void	reset_user_input( char *user_input );
bool	check_answer( char* user_input, char **answers );
bool	get_input( char *user_input );
void	run( t_data *data );


/*						*/
/*		GUESS DICO		*/
/*						*/
void	dico_correct_answer( int *good, unsigned int rank_to_del, uint8_t *nb_correct );
bool	dico_wrong_answer( t_data *data, int rank, char **right_answers );
bool    guess_dico( t_data *data );


/*						*/
/*		GUESS PRIO		*/
/*						*/
void	prio_right_answer( t_data *data, unsigned int rank_to_del );
void	prio_wrong_answer( uint8_t *nb_fails, char **right_answer );
bool	guess_prio( t_data *data );

#endif