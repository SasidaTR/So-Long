#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include <stdarg.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>

# define BUFFER_SIZE 32

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

typedef struct s_dfs
{
	int			**visited;
	char		target;
	int			*collectibles;
}	t_dfs;

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

// utils
void	error_exit(char *message);
int		close_window(t_game *game);
void	count_things(t_map *map, t_count *count);

// src
int		get_next_line(int fd, char **line);
void	get_map_size(char *file, t_map *map);
void	display_map(t_game *game, t_map *map);
int		key_press(int keycode, t_game *game);
void	validate_map_playable(t_game *game, t_map *map);

#endif
