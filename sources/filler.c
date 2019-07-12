/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftrujill <ftrujill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 22:25:35 by ftrujill          #+#    #+#             */
/*   Updated: 2019/07/12 11:27:48 by ftrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "../libft/libft.h"

int     prt_error(int fd)
{
    ft_putstr_fd("ERROR\n", fd);
    close(fd);
    return (-1);
}

int     prt_error_init(int fd)
{
    ft_putstr_fd("ERROR init\n", fd);
    close(fd);
    return (-1);
}

int     prt_error_piece(int fd)
{
    ft_putstr_fd("ERROR piece\n", fd);
    close(fd);
    return (-1);
}

void prt_all(char **line, int fd)
{
    while(get_next_line(0, line))
        {
            ft_putstr_fd(*line, fd);
            write(fd, "\n", 1);
            free(*line);
        }
}

void prt_tab(t_tab *tab, int fd)
{
    int i;

    i = 0;
    ft_putnbr_fd(tab->x, fd);
            write(fd, "\n", 1);
    ft_putnbr_fd(tab->y, fd);
            write(fd, "\n", 1);  
    while (i < tab->x)
    {
        ft_putstr_fd(tab->tab[i++], fd);
        write(fd, "\n", 1);
    }
}

void    free_tab(t_tab *tab)
{
    int i;

    i = 0;
    while (i < tab->x)
        free(tab->tab[i++]);
    free(tab->tab);
    free(tab);
}

void    free_all(char **line, t_tab *map, t_tab *piece)
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

int     copy_piece(char *line, t_tab *piece, int fd)
{
    int i;
    int j;
    char c;

    ft_memset(line, 0, 50);
    read(0, line, 1);
    while (!ft_isdigit(*line))
        read(0, line, 1);
    i = 1;
      
    while (read(0, line + i, 1) && ft_isdigit(line[i]))
        i++;
   
    piece->x = ft_atoi(line);
    ft_memset(line, 0, 50);
    read(0, line, 1);
    while (!ft_isdigit(*line))
        read(0, line, 1);
    i = 1;
    while (read(0, line + i, 1) && ft_isdigit(line[i]))
        i++;
    piece->y = ft_atoi(line);
    ft_putnbr_fd(piece->x, fd);
    ft_putnbr_fd(piece->y, fd);
    i = 0;
    while (i < piece->x)
    {
        j = 0;
        while (read(0, &c, 1) && j < piece->y)
        {
            if (c == '.' || c == '*')
                {
                    piece->tab[i][j] = c;
                    j++;
                }
            
        }
        piece->tab[i][j] = '\n';
        ft_putstr_fd(piece->tab[i], fd);
    i++;
    }
    /* If I ask him to read one more it stops working...
    
    ft_putstr_fd("Here is the number ", fd);
    ft_putnbr_fd(read(0, line, 1), fd);
     while(c)
    {
        ft_putnbr_fd(c, fd);
        c = read(0, line, 1);
    }*/
    return (1);
}

void    reset_map(t_tab *map)
{
    int i;

    i = 0;
    while (i < map->x)
            ft_memset(map->tab[i++], 0, map->y + 1);
}

void     reset_piece(t_tab *piece, t_tab *map)
{
    int i;

    i = 0;
    while (i < map->x)
            ft_memset(piece->tab[i++], 0, map->y + 1);
}

int     copy_map(t_tab *map, int fd)
{
    int i;
    int j;
    char c;

    i = 0;
    while (i < map->x)
    {
        j = 0;
        while (read(0, &c, 1) && j < map->y)
        {
            if (c == '.' || c == 'O' || c == 'X')
                {
                    map->tab[i][j] = c;
                    j++;
                }
        }
        map->tab[i][j] = '\n';
        ft_putstr_fd(map->tab[i], fd);
    i++;
    }
    /* read(0, line, 4);
    read(0, map->tab[i], map->y + 1);
    ft_putstr_fd(map->tab[i], fd);*/
    return (1);
}

void     min_piece(t_tab *piece)
{
    int i;
    int j;

    i = 0;
    piece->x_max = 0;
    piece->x_min = piece->x - 1;
    piece->y_max = 0;
    piece->y_min = piece->y - 1;
    while (i < piece->x)
    {
        j = 0;
        while (j < piece->y)
        {
            if (piece->tab[i][j] == '*')
            {
                piece->x_min = ft_min_int(piece->x_min, i);
                piece->x_max = ft_max_int(piece->x_max, i);
                piece->y_min = ft_min_int(piece->y_min, j);
                piece->y_max = ft_max_int(piece->y_max, j);   
            }
            j++;
        }
        i++;
    }
}

int     valid_pos(t_tab *map, t_tab *piece, int x, int y, int fd)
{
    int i;
    int j;
    int r;

    (void)fd;
    if (!(x + piece->x_min >= 0 && x + piece->x_max < map->x
        && y + piece->y_min >= 0 && y + piece->y_max < map->y))
        return (0);
    r = 0;
    i = piece->x_min;
    while (i <= piece->x_max)
    {
        j = piece->y_min;
        while (j <= piece->y_max)
        {
            if (piece->tab[i][j] == '.')
                j++;
            else
            {
                if (piece->tab[i][j] == '*' && map->tab[x + i][y + j] == piece->c)
                    return (0);
                if (piece->tab[i][j] == '*' && map->tab[x + i][y + j] == map->c)
                    r++;
                if (r > 1)
                    return (0);
                j++;
            }
        }
        i++;
    }
  /*   write(fd, "\nPosition ", 10);
    ft_putnbr_fd(x, fd);
    write(fd, " ", 1);
    ft_putnbr_fd(y, fd);
    write(fd, " ", 1);
    ft_putnbr_fd(r, fd);
*/
    return (r);
}

int     ft_abs(int x)
{
    return (x < 0 ? -x : x);
}

int     ngbs(t_tab *map, int i, int j)
{
    int x;
    int y;
    int nb;

    nb = 0;
    x = i > 0 ? i - 1 : 0;
    while (x < map->x && x <= i + 1)
    {
        y = j > 0 ? j - 1 : 0;
        while(y < map->y && y <= j + 1)
        {
            if (map->tab[x][y] == '.')
                nb++;
            y++;
        }
        x++;
    }
    return (nb);
}

int     distance(t_tab *map, t_tab *piece, int x, int y)
{
    int i;
    int j;
    int min;
    int nb;

    i = 0;
    nb = 0;
    min = 0;
    while (i < map->x)
    {
        j = 0;
        while (j < map->y)
        {
            nb = ngbs(map, i, j);
            if (map->tab[i][j] == piece->c && nb > 0)
                min += nb * (ft_abs(x - i) + ft_abs(y - j));
            j++;
        }
        i++;
    }
    return (min);
}

int    write_pos(t_tab *map, t_tab *piece, int fd)
{
    int x;
    int y;
    int best_x;
    int best_y;
    int min;

    min_piece(piece);
    best_x = -map->x;
    best_y = -map->y;
    min = -1;
    x = -map->x + 1;
    while (x < map->x)
    {
        y = -map->y + 1;
        while (y < map->y)
        {
            if (valid_pos(map, piece, x, y, fd))
                {
                    if (min < 0 || distance(map, piece, x, y) <= min)
                    {
                        best_x = x;
                        best_y = y;
                        min = distance(map, piece, x, y);
                    }
                }
            y++;
        }
        x++;
    }
    ft_putstr_fd("Got here\n", fd);

    ft_putstr_fd("\n pxy_min_max \n", fd);
        ft_putnbr_fd(piece->x_min, fd);
    write(fd, " ", 1);
        ft_putnbr_fd(piece->x_max, fd);
    write(fd, " ", 1);
        ft_putnbr_fd(piece->y_min, fd);
    write(fd, " ", 1);
        ft_putnbr_fd(piece->y_max, fd);
    write(fd, " ", 1);

    ft_putnbr(best_x);
    write(1, " ", 1);
    ft_putnbr(best_y);
    write(1, "\n", 1);
    ft_putnbr_fd(best_x, fd);
    write(fd, " ", 1);
    ft_putnbr_fd(best_y, fd);
    write(fd, "\n", 1);
    return (best_x != -map->x ? 1 : 0);
}

int     pass_lines(int n)
{
    char c;
    int i;

    i = 0;
    while (i < n)
    {
        read(0, &c, 1);
        while (c != '\n')
             read(0, &c, 1);
        i++;
    }
    return (1);
}

int     main()
{

    int fd;
    int fd2;
    char c;
    t_tab   *map;
    t_tab   *piece;
    char    *line;
    int i;

    if (!(map = (t_tab*)malloc(sizeof(t_tab))) || 
        !(piece = (t_tab*)malloc(sizeof(t_tab))) ||
        !(line = (char*)ft_memalloc(50)))
        return (0);
    fd = open("file", O_RDWR | O_CREAT, 0777);
    fd2 = open("map", O_RDWR | O_CREAT, 0777);
    
    //INIT_BEGIN
    read(0, line, 24);
    map->c = line[10] == '1' ? 'O' : 'X';
    piece->c = line[10] == '1' ? 'X' : 'O';
    ft_putstr_fd(line, fd2);
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
    ft_putnbr_fd(map->x, fd2);
    ft_putnbr_fd(map->y, fd2);
    if (!(map->tab = (char**)malloc(sizeof(char*) * (map->x + 1))))
        return (0);
    if (!(piece->tab = (char**)malloc(sizeof(char*) * (map->x + 1))))
        return (0);
    i = 0;
    while (i < map->x)
    {
        if (!(map->tab[i] = (char*)ft_memalloc(map->y + 1)))
            return (0);
        if(!(piece->tab[i] = (char*)ft_memalloc(map->y + 1)))
            return (0);
        i++;
    }
    ///map->tab[i] = 0;
    //piece->tab[i] = 0;
    //INIT ENDS
    ft_memset(line, 0, 50);
    read(0, line, map->y + 6);
    ft_putstr_fd(line, fd2);
    reset_map(map);
    copy_map(map, fd2);
    reset_piece(piece, map);
    copy_piece(line, piece, fd2);
    c = write_pos(map, piece, fd2);
    while (c)
    {
        i = 0;
        while (i < 2)
        {
            read(0, line, 1);
            while (*line != '\n')
            {
                read(0, line, 1);
            }
            i++;
        }
        write(fd2, "END\n", 4);
        ft_memset(line, 0, 50);
        reset_map(map);
        copy_map(map, fd2);
        reset_piece(piece, map);
        copy_piece(line, piece, fd2);
        c = write_pos(map, piece, fd2);
    }
    close (fd);
    close (fd2);
    return (0);
}
