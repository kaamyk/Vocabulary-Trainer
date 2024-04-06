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

// typedef struct  s_data
// {
//     char    *to_guess;
//     char    **answers;
// }               t_data;

/*					*/
/*		UTILS		*/
/*					*/
	/* print */
void	print_tab( char **t );
void	print_prioritaries( int *p );
void	print_results( __uint8_t nb_fails, __uint8_t nb_correct );
	/* free */
void	free_tab( void **t );
	/* lenght */
unsigned int	len_file( FILE *file );
unsigned int	len_prioritaries( int *prioritaries );
uint8_t	len_tab( char **t );
	/* Allocation */
char	**tabdup( char **t );
bool	init_tab( char **tab, const unsigned int l );
	/* Modify values */
void	del_char( char *s, char c );
	/* Define values */
uint8_t	define_word_to_guess( char **splitted_line );
void    define_key_value_pair( char *key, char **values, unsigned int *rank_dico );


/*					*/
/*		FILES		*/
/*					*/
int		parse_priority_words( char *buf );
bool	read_priority_words( int **prioritaries );
bool	reset_prioritary_file( int *prioritaries );
bool		error_parse_dictionary( size_t file_len, char **splitted_line, char *buf, FILE *file );
bool	parse_dictionary( void );


/*				*/
/*		RUN		*/
/*				*/
bool	parse_user_input( char* user_input );
void	reset_user_input( char *user_input );
bool	check_answer( char* user_input, char **answers );
bool	get_input( char *user_input );
void	run( int **prioritaries );


/*						*/
/*		GUESS DICO		*/
/*						*/
void	dico_correct_answer( int *good, unsigned int rank_to_del, __uint8_t *nb_correct );
bool	dico_wrong_answer( int **prioritaries, unsigned int *len_prio, __uint8_t *nb_fails, int rank, char **right_answers );
bool	check_rank( int rank, int *good, int len );
bool    guess_dico( int **prioritaries, unsigned int *len_prio, __uint8_t *nb_fails, __uint8_t *nb_correct );


/*						*/
/*		GUESS PRIO		*/
/*						*/
void	prio_right_answer( __uint8_t *nb_correct, int **prioritaries, unsigned int *len_prio, unsigned int rank_to_del );
void	prio_wrong_answer( __uint8_t *nb_fails, char **right_answer );
bool	guess_prio( int **prioritaries, unsigned int *len_prioritaries, __uint8_t *nb_fails, __uint8_t *nb_correct );

#endif