#ifndef GERMAN
#define GERMAN

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <strings.h>
#include <time.h>
#include <signal.h>
#include <ctype.h>
#include <errno.h>
#include <stddef.h>
#include <locale.h>
#include <wchar.h>

#include "color.h"

#define MAX_LEN_INPUT 46
#define NB_CORRECT 20
#define NB_FAIL 10
#define MAX_INVALID_LINE 10
#define LEN_ANSWERS 5

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 127
# endif


typedef struct s_list
{
	wchar_t			*content;
	struct s_list	*next;
}					t_list;

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
	int	err_code;
}               t_data;

/*					*/
/*		UTILS		*/
/*					*/
	// print
void	print_tab( wchar_t **t );
void	print_int_tab( int *t );
void	print_results( int nb_fails, int nb_correct );

	// lenght
int	l_tab( wchar_t **t );

	// Allocation
wchar_t	**ft_split(wchar_t const *s, wchar_t c);
wchar_t	**init_answers( void );

	// Modify values
void	del_nl( wchar_t *s );
wchar_t	**init_answers( void );
	// Define values

	// Other
bool	get_input( wchar_t *user_input );
wchar_t	*find_first_not_of( wchar_t *to_find, wchar_t *str );
bool	find_int_in_tab( int n, int *t );
bool	check_answer( wchar_t *user_input, wchar_t **answers );
int	ft_wcschr( wchar_t *s, wchar_t to_find );
int	strcmp_spe_wchar_t( wchar_t *s1, wchar_t *s2, wchar_t *rpl, wchar_t sp_c );

wchar_t	*ft_itoa(int n);

/*							*/
/*		GET_LINE_WLINE		*/
/*							*/
int	ft_nlinstr(wchar_t *s);
wchar_t	*ft_calloc(size_t nmemb, size_t size);
int	ft_lstclear(t_list **lst, void (*del)(void *));
void	*ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_assigne(t_list **l, t_list **n_elm, t_list **tmp, int n);
wchar_t	*ft_cpylst(t_list *lst, int mult, int lastlen);
wchar_t	*ft_resetrest(wchar_t *rest, wchar_t *s, int i);
wchar_t	*ft_readfile( FILE *file );
int	ft_lstnew(t_list **n_elm,  FILE *file );
wchar_t	*get_next_wline( FILE *file );

/*						*/
/*		FT_WCTOI		*/
/*						*/
int	ft_wctoi(const wchar_t *nptr);

/*					*/
/*		FREE		*/
/*					*/
wchar_t	**ft_freetab(wchar_t ***s);
void	free_loop( wchar_t **buf, wchar_t **user_input );
void	free_guess( wchar_t **to_guess, wchar_t ***answers );
void	free_data( t_data **data );

/*					*/
/*		ERROR		*/
/*					*/
int print_error( int err_code );
bool	error_guess( int err_code, wchar_t **to_guess, wchar_t ***answers, t_data *data );
bool	error_loop( int err_code, wchar_t **user_input, wchar_t **buf, t_data *data );
bool	error_reset( int err_code, t_data *data );

/*					*/
/*		FILES		*/
/*					*/
int	len_file( const char *file_name );
void	parse_priority_error( char *err_mess, wchar_t *buf, t_data *data );
bool	atoi_file( t_data *data );
bool	parse_priority_file( t_data *data );
bool	reset_prioritary_file( t_data *data );
bool	parse_dictionary_line( wchar_t *buf, int l_nb, t_data *data );


/*						*/
/*		GUESS DICO		*/
/*						*/
void	dico_right_answer( int l_nb, t_data *data );
void	dico_wrong_answer( int l_nb, wchar_t **answers, t_data *data );
bool	guess_dictionary( t_data *data );


/*						*/
/*		GUESS PRIO		*/
/*						*/
void	prio_wrong_answer( wchar_t **answers, t_data *data );
void	prio_right_answer( int l_nb, t_data *data );
bool	guess_priority( t_data *data );

/*				*/
/*		RUN		*/
/*				*/
int	guess_err( wchar_t *err_mess, wchar_t **buf, wchar_t **to_guess, wchar_t ***answers, t_data *data);
bool	define_guess_answers( wchar_t *to_guess, wchar_t **answers, wchar_t *buf );
bool	jump_to_line( int *i, int l_nb[2], t_data *data );
bool	guess_loop( wchar_t *to_guess, wchar_t **answers, t_data *data, const bool is_dico );
bool	run( t_data *data );


/*					*/
/*		MAIN		*/
/*					*/
t_data	*init_data( void );

#endif