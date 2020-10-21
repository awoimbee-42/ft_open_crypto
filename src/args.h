/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 15:44:42 by awoimbee          #+#    #+#             */
/*   Updated: 2020/10/21 12:31:25 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARGS_H
# define ARGS_H

#include <inttypes.h>
#include <stdbool.h>

typedef struct	s_digest_args
{
	bool		echo;
	bool		quiet;
	bool		rev_fmt;
	bool		str;
	char		*input;
}				t_digest_args;

t_digest_args parse_digest_args(char *av[]);

#endif
