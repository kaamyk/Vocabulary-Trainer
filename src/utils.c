#include "../inc/german.h"

void	print_tab( char **t ){
	for (char **ptr = t; ptr != NULL && *ptr != NULL; ptr++){
		write(1, *ptr, strlen(*ptr));
		write(1, "\n", 1);
	}
}

void	print_prioritaries( int *p ){
	for (unsigned int i = 0; p[i] != -1; i++){
		printf("prio[%d] = %d\n", i, p[i]);
	}
}

void	free_tab( void **t ){
	for (unsigned int i = 0; t[i]; i++){
		free(t[i]);
	}
	free(t);
	t = NULL;
}

void	free_data( const unsigned int len, t_data *data ){
	for (unsigned int i = 0; i < len; i++){
		if (data[i].to_guess != NULL){
			free(data[i].to_guess);
		}
		if (data[i].answers != NULL){
			char	**ptr = data[i].answers;
			for (unsigned int j = 0; ptr[j] != NULL; j++){
				free(ptr[j]);
			}
			free(ptr);
		}
	}
	free(data);
	data = NULL;
}

unsigned int    get_file_len( FILE *file ){
    char    *buf = NULL;
    size_t  n = 0;
    unsigned int    len = 0;

    while (getline(&buf, &n, file) != -1){
        ++len;
    }
    fseek(file, 0, SEEK_SET);
    free(buf);
    return (len);
}

unsigned int	get_len_dico( t_data *dico ){
	if (dico == NULL){
		write(1, ">>> dico is empty\n", 19);
		return (0);
	}
	
	unsigned int l = 0;
	while (dico[l].answers != NULL && dico[l].to_guess != NULL){
		l++;
	}
	return (l);
}

unsigned int	get_len_prioritaries( int *prioritaries ){
	unsigned int l = 0;
	while (prioritaries[l] != -1){
		l++;
	}
	return (l);
}

char	**tabdup( char **t ){
	char	**res = NULL;

	if (t == NULL){
		write(2, ">>> Error: duptab(): no input tab.\n", 36);
		return (NULL);
	}
	char	**ptr = t;
	while (*ptr != NULL){
		ptr++;
	}
	res = malloc(sizeof(char *) * (ptr - t + 1));
	if (res == NULL){
		write(2, ">>> Error: read_file()->duptab(): res allocation failed.\n", 58);
		return (NULL);
	}
	res[ptr - t] = NULL;
	for (unsigned int i = 0; t[i] != NULL && i < ptr - t; i++){
		res[i] = ft_strdup(t[i]);
		if (res[i] == NULL){
			// error
		}
	}
	return (res);
}