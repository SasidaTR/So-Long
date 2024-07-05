#include "../include/so_long.h"

void	move_player(t_game *game, int new_x, int new_y)
{
	if (game->map->map[game->player_y + new_y ][game->player_x + new_x] == '1')
		printf("Invalid move\n");
	else
	{
		game->map->map[game->player_y][game->player_x] = '0';
		game->player_x += new_x;
		game->player_y += new_y;
		game->map->map[game->player_y][game->player_x] = 'P';
		display_map(game, game->map);
	}
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == 65307)
		close_window(game);
	else if (keycode == 119)
		move_player(game, 0, -1);
	else if (keycode == 115)
		move_player(game, 0, 1);
	else if (keycode == 97)
		move_player(game, -1, 0);
	else if (keycode == 100)
		move_player(game, 1, 0);
	return (0);
}
