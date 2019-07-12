/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftrujill <ftrujill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 14:47:22 by ftrujill          #+#    #+#             */
/*   Updated: 2019/07/12 15:28:46 by ftrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "../libft/libft.h"

void	initialize(char *line, t_tab *piece, t_tab *map)
{
	int i;

	read(0, line, 34);
	map->c = line[10] == '1' ? 'O' : 'X';
	piece->c = line[10] == '1' ? 'X' : 'O';
	read(0, line, 8);
	ft_memset(line, 0, 50);
	i = 0;
	while (read(0, line + i, 1) && ft_isdigit(line[i]))
		i++;
	map->x = ft_atoi(line);
	ft_memset(line, 0, 50);
	i = 0;
	while (read(0, line + i, 1) && ft_isdigit(line[i]))
		i++;
	map->y = ft_atoi(line);
}

void	free_tab(t_tab *tab)
{
	int i;

	i = 0;
	while (i < tab->x)
		free(tab->tab[i++]);
	free(tab->tab);
	free(tab);
}

void	free_all(char **line, t_tab *map, t_tab *piece)
{
	int i;

	i = 0;
	while (i <= map->x)
	{
		free(map->tab[i]);
		free(piece->tab[i++]);
	}
	free(map->tab);
	free(piece->tab);
	free(map);
	free(piece);
	free(line);
}

void	reset_map(t_tab *map)
{
	int i;

	i = 0;
	while (i < map->x)
		ft_memset(map->tab[i++], 0, map->y + 1);
}

void	reset_piece(t_tab *piece, t_tab *map)
{
	int i;

	i = 0;
	while (i < map->x)
		ft_memset(piece->tab[i++], 0, map->y + 1);
}
