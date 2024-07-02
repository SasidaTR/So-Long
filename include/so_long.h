/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trischma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:09:26 by trischma          #+#    #+#             */
/*   Updated: 2024/06/21 12:46:53 by trischma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>

# define BUFFER_SIZE 32

typedef struct s_game
{
	char	*map_file;
	void	*mlx;
	void	*win;
	void	*zero;
	void	*one;
	int		img_width;
	int		img_height;
}	t_game;

typedef struct s_map
{
	char	*map_file;
	void	*zero;
	void	*one;
}	t_map;

typedef struct s_design
{
	int		img_width;
	int		img_height;
}	t_design;

// libft
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);

// src
int		get_next_line(int fd, char **line);
void	error_exit(char *message);
void	display_map(t_game *game);

#endif
