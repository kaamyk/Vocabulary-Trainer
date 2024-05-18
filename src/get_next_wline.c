#include "../inc/german.h"

int	ft_nlinstr(wchar_t *s)
{
	int	i;

	if (!s)
		return (0);
	i = 1;
	while (*s)
	{
		if (*s == '\n' || !*(s + 1))
			return (i);
		s++;
		i++;
	}
	return (i);
}

int	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*l_ptr = NULL;
	t_list	*nextlst = NULL;

	if (!lst || !del)
		return (0);
	l_ptr = *lst;
	while (l_ptr)
	{
		nextlst = l_ptr->next;
		ft_lstdelone(l_ptr, free);
		l_ptr = nextlst;
	}
	*lst = NULL;
	return (1);
}

void	*ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (lst->content)
		del(lst->content);
	del(lst);
	return (NULL);
}

void	ft_assigne(t_list **l, t_list **n_elm, t_list **tmp, int n)
{
	if (!n)
	{
		(*l) = (*n_elm);
		(*tmp) = (*l);
	}
	else
	{
		(*l)->next = (*n_elm);
		(*l) = (*l)->next;
	}
}

wchar_t	*ft_cpylst(t_list *lst, int mult, int lastlen)
{
	t_list	*l_tmp = NULL;
	int		i = 0;
	int		j = 0;
	wchar_t	*s = (wchar_t *)calloc(BUFFER_SIZE * mult + lastlen + 1, sizeof(wchar_t));

	if (!s || !lst || !lst->content)
		return (NULL);
	l_tmp = lst;
	while (l_tmp)
	{
		j = 0;
		while (l_tmp->content[j] && ++i && ++j)
		{
			s[i - 1] = l_tmp->content[j - 1];
			if (s[i - 1] == '\n' && ft_lstclear(&lst, free))
				return (s);
		}
		l_tmp = l_tmp->next;
	}
	ft_lstclear(&lst, free);
	return (s);
}

wchar_t	*ft_resetrest(wchar_t *rest, wchar_t *s, int i)
{
	wchar_t	tmp = 0;
	int		j = 0;

	while (s && rest[i] && i < BUFFER_SIZE && ++i && ++j)
	{
		tmp = rest[i - 1];
		rest[j - 1] = tmp;
	}
	while (j < BUFFER_SIZE && ++j)
		rest[j - 1] = 0;
	return (s);
}

wchar_t	*ft_readfile( FILE *file )
{
	static wchar_t	rest[BUFFER_SIZE + 1];
	int			i = 0;
	int			j = 0;
	wchar_t		*s = (wchar_t *)calloc(BUFFER_SIZE + 1, sizeof(wchar_t));
	if (s == NULL)
		return (NULL);

	while (s && rest[i] && i < BUFFER_SIZE && ++i)
	{
		s[i - 1] = rest[i - 1];
		if (s[i - 1] == '\n')
			return (ft_resetrest(rest, s, i));
	}
	ft_resetrest(rest, s, i);
	if (!*rest && !fread(rest, sizeof(wchar_t), BUFFER_SIZE, file))
		return (s);
	while (s && rest[j] && i < BUFFER_SIZE && ++j && ++i)
	{
		s[i - 1] = rest[j - 1];
		if (s[i - 1] == '\n')
			return (ft_resetrest(rest, s, j));
	}
	ft_resetrest(rest, s, j);
	return (s);
}

int	ft_lstnew( t_list **n_elm, FILE *file )
{
	int	i = 0;

	*n_elm = (t_list *)malloc (sizeof(t_list));
	if (!*n_elm)
		return (1);
	(*n_elm)->content = ft_readfile(file);
	(*n_elm)->next = NULL;
	while (i < BUFFER_SIZE && ++i)
	{
		if (!(*n_elm)->content[0] || (*n_elm)->content[i - 1] == '\n')
			return (1);
	}
	return (0);
}

// wchar_t	*get_next_wline(int fd)
wchar_t	*get_next_wline( FILE *file )
{
	t_list	*n_elm = NULL;
	t_list	*l = NULL;
	t_list	*tmp = NULL;
	wchar_t	*s = NULL;
	int		i = 0;

	if (BUFFER_SIZE <= 0)
		return (NULL);
	while (!ft_lstnew(&n_elm, file) && ++i && n_elm->content)
	{
		if (!l)
			ft_assigne(&l, &n_elm, &tmp, 0);
		else
			ft_assigne(&tmp, &n_elm, &tmp, 1);
	}
	if (n_elm->content[0] && !i)
		ft_assigne(&l, &n_elm, &tmp, 0);
	else if (i)
		ft_assigne(&tmp, &n_elm, &tmp, 1);
	else if (!n_elm->content[0] && !i)
		return (ft_lstdelone(n_elm, free));
	s = ft_cpylst(l, i, ft_nlinstr(tmp->content));
	return (s);
}