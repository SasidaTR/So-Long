#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>

# define BUFFER_SIZE 32

typedef struct s_design
{
	int		img_width;
	int		img_height;
}	t_design;

typedef struct s_map
{
	char	*map_file;
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

// src
int		get_next_line(int fd, char **line);
void	error_exit(char *message);
int		close_window(t_game *game);
void	get_map_size(char *file, int *width, int *height);
void	display_map(t_game *game, t_map *map);
void	redraw_map(t_game *game, t_map *map);
int		key_press(int keycode, t_game *game);

#endif
