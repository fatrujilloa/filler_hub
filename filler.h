/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftrujill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 22:27:42 by ftrujill          #+#    #+#             */
/*   Updated: 2019/06/17 15:13:21 by ftrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct	s_tab
{
	char		c;
	int         x;
    int         y;
	int			x_min;
	int			x_max;
	int			y_min;
	int			y_max;
	char		**tab;
}				t_tab;

typedef struct	s_map
{
	char		c;
	int         x;
    int         y;
	int			p_x;
	int			p_y;
	int			l_size;
	char		**map;
	char		**piece;
}				t_map;

#endif