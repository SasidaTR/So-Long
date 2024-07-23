/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trischma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:53:15 by trischma          #+#    #+#             */
/*   Updated: 2024/07/11 15:55:45 by trischma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	error_exit_two(t_game *game, t_map *map, char *message)
{
	free_map(map);
	free_game_resources(game);
	perror(message);
	exit(EXIT_FAILURE);
}
