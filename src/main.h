/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 18:03:59 by awoimbee          #+#    #+#             */
/*   Updated: 2020/10/19 19:23:53 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdbool.h>
# include <stddef.h>
# include <sys/types.h>

typedef	int(t_main_fn)(int, char *[]);

typedef struct	s_main_cmds
{
	char		*name;
	t_main_fn	*fn;
}				t_main_cmd;

int				main_md5(int ac, char *av[]);
int				main_sha256(int ac, char *av[]);

#endif
