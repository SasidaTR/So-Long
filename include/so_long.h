/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trischma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:54:44 by trischma          #+#    #+#             */
/*   Updated: 2024/07/11 16:00:01 by trischma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include <stdarg.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>

# define BUFFER_SIZE 32
# define NUM_SPRITES 4

typedef struct s_dfs
{
	int			**visited;
	char		target;
	int			*collectibles;
}	t_dfs;

typedef struct s_count
{
	int			collectables;
	int			players;
	int			exits;
	int			move_count;
}	t_count;

typedef struct s_design
{
	int			img_width;
	int			img_height;
	void		*player_img_up;
	void		*player_img_down;
	void		*player_img_left;
	void		*player_img_right;
	void		*current_player_img;
	void		*m_imgs[NUM_SPRITES];
	int			current_monster_img;
}	t_design;

typedef struct s_map
{
	char		*map_file;
	char		**map;
	int			width;
	int			height;
	void		*zero;
	void		*one;
	void		*c;
	void		*e;
	void		*m;
	void		*p;
	t_design	*design;
}	t_map;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	int			player_x;
	int			player_y;
	int			collectables;
	int			total_collectables;
	t_map		*map;
	t_count		*count;
}	t_game;

// libft
char	*ft_itoa(int n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_strchr(const char *s, int c);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
int		ft_putchar(char c);
int		ft_putstr(char *str);
int		ft_putnbr(int n);
int		ft_putnbr_u(unsigned int n);
int		ft_puthex(unsigned long n);
int		ft_puthex_upper(unsigned int n);
int		ft_putptr(void *ptr);
int		ft_printf(const char *format, ...);

// src
int		get_next_line(int fd, char **line);
void	find_player_position(t_game *game, t_map *map);
void	get_map_size(t_game *game, char *file, t_map *map);
void	display_map(t_game *game, t_map *map);
int		key_press(int keycode, t_game *game);
void	validate_map_border(t_game *game, t_map *map);
void	validate_map_playable(t_game *game, t_map *map);
void	free_visited(int **visited, int height);
void	free_game_resources(t_game *game);
void	error_exit(t_game *game, char *message);
void	error_exit_two(t_game *game, t_map *map,char *message);
int		close_window(t_game *game);
void	count_things(t_game *game, t_map *map, t_count *count);
void	free_map(t_map *map);

#endif
