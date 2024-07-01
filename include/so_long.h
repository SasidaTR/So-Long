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

#include <mlx.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

typedef struct	s_game {
	void	*mlx;
	void	*win;
	void	*img1;
	void	*img2;
	int		img_width;
	int		img_height;
	char	**map;
	int		map_width;
	int		map_height;
}				t_game;

#endif
