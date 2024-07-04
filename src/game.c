#include "../include/so_long.h"

int	is_valid_move(t_map *map, int x, int y)
{
	if (x < 0 || x >= map->width || y < 0 || y >= map->height)
		return (0);
	return (map->map_file[y * map->width + x] != '1');
}

void	move_player(t_game *game, int new_x, int new_y)
{
	if (is_valid_move(game->map, new_x, new_y))
	{
		game->map->map_file[game->player_y * game->map->width + game->player_x] = '0';
		game->player_x = new_x;
		game->player_y = new_y;
		game->map->map_file[game->player_y * game->map->width + game->player_x] = 'P';
		redraw_map(game, game->map);
	}
	else
		printf("Invalid move\n");
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == 65307)
		close_window(game);
	else if (keycode == 119)
		move_player(game, game->player_x, game->player_y - 1);
	else if (keycode == 115)
		move_player(game, game->player_x, game->player_y + 1);
	else if (keycode == 97)
		move_player(game, game->player_x - 1, game->player_y);
	else if (keycode == 100)
		move_player(game, game->player_x + 1, game->player_y);
	return (0);
}
