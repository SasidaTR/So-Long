#include "../include/so_long.h"

void	display_move_count(t_game *game)
{
	char	*move_count_str;

	move_count_str = ft_itoa(game->count->move_count);
	if (!move_count_str)
		error_exit("Failed to convert move count to string");
	mlx_string_put(game->mlx, game->win, 10, 10, 0x000000, move_count_str);
	free(move_count_str);
}

void	update_player(t_game *game, int new_x, int new_y)
{
	game->map->map[game->player_y][game->player_x] = '0';
	game->player_x += new_x;
	game->player_y += new_y;
	game->map->map[game->player_y][game->player_x] = 'P';
	if (new_y == -1)
		game->map->design->current_player_img
			= game->map->design->player_img_up;
	else if (new_y == 1)
		game->map->design->current_player_img
			= game->map->design->player_img_down;
	else if (new_x == -1)
		game->map->design->current_player_img
			= game->map->design->player_img_left;
	else if (new_x == 1)
		game->map->design->current_player_img
			= game->map->design->player_img_right;
}

void	move_player(t_game *game, int new_x, int new_y)
{
	char	next_cell;

	next_cell = game->map->map[game->player_y + new_y][game->player_x + new_x];
	if (next_cell == '1')
		ft_printf("Invalid move\n");
	else if (next_cell == 'E')
	{
		if (game->collectables < game->total_collectables)
			ft_printf("Collect all items before exiting\n");
		else
		{
			ft_printf("You win with %d moves!\n", game->count->move_count + 1);
			close_window(game);
		}
	}
	else if (next_cell == 'M')
	{
		ft_printf("You've been caught by police: jail.\n");
		close_window(game);
	}
	else
	{
		if (next_cell == 'C')
			game->collectables++;
		update_player(game, new_x, new_y);
		game->count->move_count++;
		display_map(game, game->map);
		display_move_count(game);
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
