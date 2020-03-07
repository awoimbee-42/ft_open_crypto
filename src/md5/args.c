/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 17:56:27 by awoimbee          #+#    #+#             */
/*   Updated: 2020/03/07 18:46:36 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_md5.h"

const t_arg args[] = {
	{"-p", NULL, 0, ft_md5}, // md5_stdin
	{"-q", NULL, 0, NULL}, // enable_quiet w/ static var
	{"-r", NULL, 0, NULL}, // set_reverse_output w/ static var
	{"-s", NULL, 1, NULL}, // md5_str
	{NULL, NULL, 0, NULL}, // md5_file -> special catch-all case
};
