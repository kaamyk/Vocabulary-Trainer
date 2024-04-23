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
<<<<<<< HEAD
#include <stdint.h>
=======
>>>>>>> 7ca858be2ac805eef042a8bc86736451b9b1c618

#include "color.h"

#define MAX_LEN_INPUT 46
#define NB_CORRECT 20
#define NB_FAIL 10
<<<<<<< HEAD
#define MAX_INVALID_LINE 10
#define LEN_ANSWERS 5
=======
>>>>>>> 7ca858be2ac805eef042a8bc86736451b9b1c618

typedef struct  s_data
{
	FILE	*file;
<<<<<<< HEAD
	int	nb_fails;
	int	nb_correct;
	int	l_dico;
	int	*priority;
	int	l_prio;
	int	*past_ranks;
	int	l_past_ranks;
	int	*invalid_lines;
	int	l_invalid_lines;
=======
	int	l_dico;
	int	*prioritaries;
	uint8_t	l_prio;
	uint8_t	nb_fails;
	uint8_t	nb_correct;
>>>>>>> 7ca858be2ac805eef042a8bc86736451b9b1c618
}               t_data;

/*					*/
/*		UTILS		*/
/*					*/
<<<<<<< HEAD
	// print
void	print_tab( char **t );
void	print_int_tab( int *t );
=======
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
uint8_t	define_word_to_guess( char **splitted_line );
void    define_key_value_pair( char **key, char ***values, int *rank_dico, FILE *file );
>>>>>>> 7ca858be2ac805eef042a8bc86736451b9b1c618

	// free
char	**ft_freetab(char ***s);
void	free_all( char **buf, char **to_guess, char ***answers );

<<<<<<< HEAD
	// lenght
int	l_tab( char **t );
=======
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
>>>>>>> 7ca858be2ac805eef042a8bc86736451b9b1c618

	// Allocation
char	**ft_split(char const *s, char c);
char	**init_answers( void );

<<<<<<< HEAD
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
=======
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
>>>>>>> 7ca858be2ac805eef042a8bc86736451b9b1c618

#endif