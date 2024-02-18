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

typedef struct  s_data
{
    char    *to_guess;
    char    **answers;
}               t_data;

    /*                  */
    /*      UTILS       */
    /*                  */
char	**tabdup( char **t );
void	free_tab( void **t );
void	free_data( const unsigned int len, t_data *data );
unsigned int    get_file_len( FILE *file );
unsigned int	get_len_dico( t_data *dico );
unsigned int    get_len_prioritaries( int *prioritaries );
void	print_tab( char **t );
void	print_prioritaries( int *p );


    /*                  */
    /*      FILES       */
    /*                  */
int     parse_priority_words( char *buf );
bool    read_priority_words( int **prioritaries );
bool    reset_prioritary_file( int *prioritaries );
void    error_read_dictionnary( t_data *word, size_t file_len, char **splitted_line, char *buf );
bool	read_dictionnary( t_data **dico );


    /*              */
    /*      RUN     */
    /*              */
void    run( int **prioritaries, t_data *word );

#endif