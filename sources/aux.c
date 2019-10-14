/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <auguyon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 17:35:00 by auguyon           #+#    #+#             */
/*   Updated: 2019/10/13 17:24:38 by auguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	initialize(t_tab *piece, t_tab *map)
{
	char *line;
	int i;

	get_next_line(0, &line);
	map->c = ft_strstr(line, "auguyon") > 0 ? 'O' : 'X';
	piece->c = map->c == 'O' ? 'X' : 'O';
	free(line);
	get_next_line(0, &line);
	i = 8;
	map->x = ft_atoi(line);
	while (line[i] != ' ')
		i++;
	map->y = ft_atoi(line);
	free(line);
}

void	reset(t_tab *piece, t_tab *map)
{
	int i;

	i = 0;
	while (i < map->x)
		ft_bzero(map->tab[i++], map->y + 1);
	i = 0;
	while (i < map->x)
		ft_bzero(piece->tab[i++], map->y + 1);
}

void	prt_pos(int best_x, int best_y)
{
	ft_putnbr(best_x);
	write(1, " ", 1);
	ft_putnbr(best_y);
	write(1, "\n", 1);
}

void	free_all(char *line, t_tab *piece, t_tab *map)
{
	int i;

	i = 0;
	free(line);
	while (i < map->x)
	{
		free(piece->tab[i]);
		free(map->tab[i++]);
	}
	free(piece->tab);
	free(piece);
	free(map->tab);
	free(map);
}
