/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 18:03:59 by awoimbee          #+#    #+#             */
/*   Updated: 2020/10/29 16:32:35 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdbool.h>
# include <stddef.h>
# include <sys/types.h>

typedef	int(t_main_fn)(int, char *[]);

typedef struct	s_cmd_from_str
{
	char		*str;
	t_main_fn	*fn;
}				t_cmd_from_str;

int		digest_main(int argc, char *argv[]);

#endif
