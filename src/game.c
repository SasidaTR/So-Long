#include "../include/so_long.h"

void	message_close(t_gmc *gmc, const char *message, int type)
{
	if (type > 0)
		ft_printf("%s %d moves\n", message, type);
	else
		ft_printf("%s", message);
	close_window(gmc);
}

void	display_move_count(t_gmc *gmc)
{
	char	*move_count_str;

	move_count_str = ft_itoa(gmc->count->move_count);
	if (!move_count_str)
		error_exit(gmc, "Failed to convert move count to string");
	ft_printf("%d\n", gmc->count->move_count);
	mlx_string_put(gmc->game->mlx, gmc->game->win,
		10, 10, 0x000000, move_count_str);
	free(move_count_str);
}

void	update_player(t_gmc *gmc, int new_x, int new_y)
{
	gmc->map->map[gmc->game->player_y][gmc->game->player_x] = '0';
	gmc->game->player_x += new_x;
	gmc->game->player_y += new_y;
	gmc->map->map[gmc->game->player_y][gmc->game->player_x] = 'P';
	if (new_y == -1)
		gmc->map->design->current_player_img
			= gmc->map->design->player_img_up;
	else if (new_y == 1)
		gmc->map->design->current_player_img
			= gmc->map->design->player_img_down;
	else if (new_x == -1)
		gmc->map->design->current_player_img
			= gmc->map->design->player_img_left;
	else if (new_x == 1)
		gmc->map->design->current_player_img
			= gmc->map->design->player_img_right;
}

void	move_player(t_gmc *gmc, int new_x, int new_y)
{
	char	next_cell;

	next_cell = gmc->map->map[gmc->game->player_y + new_y][gmc->game->player_x + new_x];
	if (next_cell == '1')
		ft_printf("Invalid move\n");
	else if (next_cell == 'E')
	{
		if (gmc->game->collectables < gmc->count->collectables)
			ft_printf("Collect all items before exiting\n");
		else
			message_close(gmc, "You win with", gmc->count->move_count + 1);
	}
	else if (next_cell == 'M')
		message_close(gmc, "You've been caught by police: jail.\n", 0);
	else
	{
		if (next_cell == 'C')
			gmc->game->collectables++;
		update_player(gmc, new_x, new_y);
		gmc->count->move_count++;
		display_map(gmc);
		display_move_count(gmc);
	}
}

int	key_press(int keycode, t_gmc *gmc)
{
	if (keycode == 65307)
		close_window(gmc);
	else if (keycode == 119)
		move_player(gmc, 0, -1);
	else if (keycode == 115)
		move_player(gmc, 0, 1);
	else if (keycode == 97)
		move_player(gmc, -1, 0);
	else if (keycode == 100)
		move_player(gmc, 1, 0);
	return (0);
}
