#ifndef GERMAN
#define GERMAN

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "../libft/libft.h"

#define MAX_LEN_INPUT 46
#define NB_CORRECT 2
#define NB_FAIL 2

typedef struct  s_data
{
    char    *to_guess;
    char    **answers;
}               t_data;

    /*					*/
    /*		 UTILS		*/
    /*					*/
char	**tabdup( char **t );
void	free_tab( void **t );
void	free_data( const unsigned int len, t_data *data );
unsigned int    get_file_len( FILE *file );
unsigned int	get_len_dico( t_data *dico );
unsigned int    get_len_prioritaries( int *prioritaries );
void	print_tab( char **t );
void	print_prioritaries( int *p );


    /*					*/
    /*		FILES		*/
    /*					*/
int     parse_priority_words( char *buf );
bool    read_priority_words( int **prioritaries );
bool    reset_prioritary_file( int *prioritaries );
void    error_read_dictionnary( t_data *word, size_t file_len, char **splitted_line, char *buf );
bool	read_dictionnary( t_data **dico );


	/*				*/
	/*      RUN		*/
	/*				*/
bool   	parse_user_input( char* user_input );
void	reset_user_input( char *user_input );
bool    check_answer( char* user_input, char **answers );
void    run( int **prioritaries, t_data *word );

	/*						*/
	/*      GUESS DICO		*/
	/*						*/
void	dico_correct_answer( int *good, unsigned int rank_to_del, __uint8_t *nb_correct );
bool	dico_wrong_answer( int **prioritaries, unsigned int *len_prio, __uint8_t *nb_fails, int rank );
bool	check_rank( int rank, int *good );
bool    guess_dico( int **prioritaries, unsigned int *len_prio, t_data *dico, __uint8_t *nb_fails, __uint8_t *nb_correct );

	/*						*/
	/*      GUESS PRIO		*/
	/*						*/
void	prio_right_answer( __uint8_t *nb_correct, int **prioritaries, unsigned int *len_prio, unsigned int rank_to_del );
void	prio_wrong_answer( __uint8_t *nb_fails, char **right_answer );
bool    guess_prio( int **prioritaries, t_data *dico, unsigned int *len_prioritaries, __uint8_t *nb_fails, __uint8_t *nb_correct );

#endif