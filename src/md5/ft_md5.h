/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 18:45:25 by awoimbee          #+#    #+#             */
/*   Updated: 2020/03/07 18:46:45 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MD5_H
# define FT_MD5_H

#include <inttypes.h>

/*
**	The argument processing in md5 is abysmal & I have to reproduce it.
**	We process each arg one after the other (so no support for repeating args).
*/
typedef void(*t_arg_callback)(void *value);

/**
**	take_value: 0 == no, 1 == yes, 2 == multiple
*/
typedef struct	s_arg
{
	char			*short_nname;
	char			*full_name;
	int				take_value;
	t_arg_callback	f;
}				t_arg;



char		*md5_get_digest();
void		md5_chunk(uint32_t *chunk);

#endif
