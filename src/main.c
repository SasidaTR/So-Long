#include "../include/so_long.h"

int	update_monster_animation(t_gmc *gmc)
{
	static int	frame_count = 0;

	frame_count++;
	if (frame_count >= 60000)
	{
		gmc->map->design->current_monster_img++;
		if (gmc->map->design->current_monster_img >= NUM_SPRITES)
			gmc->map->design->current_monster_img = 0;
		display_map(gmc);
		frame_count = 0;
	}
	return (0);
}

void	initialize_player_and_monster_images(t_gmc *gmc)
{
	gmc->map->design->player_img_up = mlx_xpm_file_to_image(gmc->game->mlx,
			"graf/b.xpm", &gmc->map->design->img_width, &gmc->map->design->img_height);
	gmc->map->design->player_img_down = mlx_xpm_file_to_image(gmc->game->mlx,
			"graf/f.xpm", &gmc->map->design->img_width, &gmc->map->design->img_height);
	gmc->map->design->player_img_left = mlx_xpm_file_to_image(gmc->game->mlx,
			"graf/l.xpm", &gmc->map->design->img_width, &gmc->map->design->img_height);
	gmc->map->design->player_img_right = mlx_xpm_file_to_image(gmc->game->mlx,
			"graf/r.xpm", &gmc->map->design->img_width, &gmc->map->design->img_height);
	gmc->map->design->current_player_img = gmc->map->design->player_img_down;
	gmc->map->design->m_imgs[0] = mlx_xpm_file_to_image(gmc->game->mlx, "graf/mb.xpm",
			&gmc->map->design->img_width, &gmc->map->design->img_height);
	gmc->map->design->m_imgs[1] = mlx_xpm_file_to_image(gmc->game->mlx, "graf/ml.xpm",
			&gmc->map->design->img_width, &gmc->map->design->img_height);
	gmc->map->design->m_imgs[2] = mlx_xpm_file_to_image(gmc->game->mlx, "graf/mf.xpm",
			&gmc->map->design->img_width, &gmc->map->design->img_height);
	gmc->map->design->m_imgs[3] = mlx_xpm_file_to_image(gmc->game->mlx, "graf/mr.xpm",
			&gmc->map->design->img_width, &gmc->map->design->img_height);
	if (!gmc->map->design->player_img_up || !gmc->map->design->player_img_down
		|| !gmc->map->design->player_img_left
		|| !gmc->map->design->player_img_right
		|| !gmc->map->design->m_imgs[0] || !gmc->map->design->m_imgs[1]
		|| !gmc->map->design->m_imgs[2] || !gmc->map->design->m_imgs[3])
		error_exit(gmc, "Failed to load player or monster images");
}

void	initialize_map_images(t_gmc *gmc)
{
	gmc->map->zero = mlx_xpm_file_to_image(gmc->game->mlx, "graf/0.xpm",
			&gmc->map->design->img_width, &gmc->map->design->img_height);
	gmc->map->one = mlx_xpm_file_to_image(gmc->game->mlx, "graf/1.xpm",
			&gmc->map->design->img_width, &gmc->map->design->img_height);
	gmc->map->c = mlx_xpm_file_to_image(gmc->game->mlx, "graf/c.xpm",
			&gmc->map->design->img_width, &gmc->map->design->img_height);
	gmc->map->e = mlx_xpm_file_to_image(gmc->game->mlx, "graf/e.xpm",
			&gmc->map->design->img_width, &gmc->map->design->img_height);
	gmc->map->m = mlx_xpm_file_to_image(gmc->game->mlx, "graf/m.xpm",
			&gmc->map->design->img_width, &gmc->map->design->img_height);
	if (!gmc->map->zero || !gmc->map->one || !gmc->map->c
		|| !gmc->map->e || !gmc->map->m)
		error_exit(gmc, "Failed to load map images");
}

void	initialize_game(t_gmc *gmc)
{
	gmc->map->design = malloc(sizeof(t_design));
	if (!gmc->map->design)
		error_exit(gmc, "Failed to allocate memory for map design");
	gmc->game->mlx = mlx_init();
	if (!gmc->game->mlx)
		error_exit(gmc, "Failed to initialize mlx");
	initialize_map_images(gmc);
	initialize_player_and_monster_images(gmc);
	gmc->game->win = mlx_new_window(gmc->game->mlx, gmc->map->width
			* gmc->map->design->img_width, gmc->map->height
			* gmc->map->design->img_height, "Nom du jeu");
	if (!gmc->game->win)
		error_exit(gmc, "Failed to create window");
}

int	main(int argc, char **argv)
{
	t_gmc	gmc;

	if (argc != 2 || ft_strlen(argv[1]) < 4
		|| ft_strcmp(argv[1] + ft_strlen(argv[1]) - 4, ".ber") != 0)
		return (ft_printf("Usage: %s <map.ber>\n", argv[0]), 1);
	gmc.game = malloc(sizeof(t_game));
	gmc.map = malloc(sizeof(t_map));
	gmc.count = malloc(sizeof(t_count));
	if (!gmc.game || !gmc.map || !gmc.count)
		return (ft_printf("Failed to allocate memory\n"), 1);
	gmc.map->map_file = argv[1];
	gmc.game->collectables = 0;
	gmc.count->move_count = 0;
	get_map_size(&gmc);
	validate_map_border(&gmc);
	find_player_position(&gmc);
	count_things(&gmc);
	validate_map_playable(&gmc);
	initialize_game(&gmc);
	display_map(&gmc);
	mlx_loop_hook(gmc.game->mlx, update_monster_animation, &gmc);
	mlx_hook(gmc.game->win, 17, 0, close_window, &gmc);
	mlx_key_hook(gmc.game->win, key_press, &gmc);
	mlx_loop(gmc.game->mlx);
	free_game_resources(&gmc);
	return (0);
}
