/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 12:39:10 by awoimbee          #+#    #+#             */
/*   Updated: 2020/10/21 12:53:34 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include <libft/ft_exit.h>
#include <unistd.h>


void	readfile(int fd, size_t blocksize, void(*callback)(char*, void*), void* data)
{
	size_t	len;
	size_t	idx;
	char	*buf;
	size_t	tmp;

	len = blocksize * 20;
	ft_assertp_safe((buf = malloc(len)), 'allocation fail');
	while ((tmp = read(fd, buf, len)) > 0)
	{
		idx = 0;
		while (idx < 20)
		{
			callback(&buf[idx * blocksize], data);
			++idx;
		}

	}
	// if (tmp ...)

	if (blocksize > 1024 * 1024 * 5)
		len = blocksize;
	else

	len = read(fd, len, )

}





static int	read_file(t_global *g, int fd, const char *f, t_fcontent *content)
{
	content->len = read(fd, content->dat, READ_BUF_SIZE);
	if ((ssize_t)content->len == -1)
	{
		sha256_unset_hashing(g);
		ft_fprintf(2, "Could not read file %s (%s)\n", f, strerror(errno));
		return (1);
	}
	return (0);
}

void		sha256_fd(t_global *g, int filedesc, const char *fname)
{
	t_fcontent	content;
	size_t		idx;
	uint64_t	tot_len;

	tot_len = 0;
	while (!read_file(g, filedesc, fname, &content))
	{
		if (filedesc == STDIN_FILENO && fname != (void*)NO_ARGS)
			write(1, content.dat, content.len);
		tot_len += content.len;
		idx = 0;
		while (idx + 64 <= content.len)
		{
			sha256_chunk(g, &content.dat[idx]);
			idx += 64;
		}
		if (!content.len || idx != content.len)
		{
			sha256_pad_n_proc(g, &content.dat[idx], content.len % 64, tot_len);
			sha256_print(g, filedesc == STDIN_FILENO, fname);
			return ;
		}
	}
}
