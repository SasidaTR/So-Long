#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>

# define BUFFER_SIZE 32

typedef struct s_counts
{
	int		collectables;
	int		players;
	int		exits;
}	t_counts;

typedef struct s_design
{
	int		img_width;
	int		img_height;
}	t_design;

typedef struct s_map
{
	char	*map_file;
	char	**map;
	int		width;
	int		height;
	void	*zero;
	void	*one;
	void	*c;
	void	*e;
	void	*p;
	t_design *design;
}	t_map;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	int		player_x;
	int		player_y;
	int		collectables;
	int		total_collectables;
	t_map	*map;
}	t_game;

typedef struct s_game_init
{
	int		width;
	int		height;
}	t_game_init;

// libft
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);

// utils
void	error_exit(char *message);
int		close_window(t_game *game);
int		is_path_valid(t_map *map);

// src
int		get_next_line(int fd, char **line);
void	get_map_size(char *file, t_map *map);
void	display_map(t_game *game, t_map *map);
void	count_things(t_map *map, t_counts *counts);
int		key_press(int keycode, t_game *game);

#endif
