#include "../includes/so_long.h"

//void print_loading_error(t_map *map) {}

bool load_textures(xpm_t **xpm)
{	
	xpm[BG] = mlx_load_xpm42("textures/starry_bg_no_clouds.xpm42");
	if (!xpm[BG])
		return (ft_putendl_fd("starry_bg_no_clouds.xpm42 was not found!", STDOUT_FILENO), false);

	xpm[WALL] = mlx_load_xpm42("textures/wall.xpm42");
	if (!xpm[WALL])
		return (ft_putendl_fd("wall.xpm42 was not found!", STDOUT_FILENO), false);

	xpm[TILE1] = mlx_load_xpm42("textures/cloud_up.xpm42");
	if (!xpm[TILE1])
		return (ft_putendl_fd("cloud_up.xpm42 was not found!", STDOUT_FILENO), false);

	xpm[TILE2] = mlx_load_xpm42("textures/cloud_down.xpm42");
	if (!xpm[TILE2])
		return (ft_putendl_fd("cloud_down.xpm42 was not found!", STDOUT_FILENO), false);

	xpm[CHAR_L_FLY1] = mlx_load_xpm42("textures/fairy_l_fly1.xpm42");
	if (!xpm[CHAR_L_FLY1])
		return (ft_putendl_fd("fairy_l_fly1.xpm42 was not found!", STDOUT_FILENO), false);

	xpm[CHAR_R_FLY1] = mlx_load_xpm42("textures/fairy_r_fly1.xpm42");
	if (!xpm[CHAR_R_FLY1])
		return (ft_putendl_fd("fairy_r_fly1.xpm42 was not found!", STDOUT_FILENO), false);

	xpm[CHAR_L_FLY2] = mlx_load_xpm42("textures/fairy_l_fly2.xpm42");
	if (!xpm[CHAR_L_FLY2])
		return (ft_putendl_fd("fairy_l_fly2.xpm42 was not found!", STDOUT_FILENO), false);

	xpm[CHAR_R_FLY2] = mlx_load_xpm42("textures/fairy_r_fly2.xpm42");
	if (!xpm[CHAR_R_FLY2])
		return (ft_putendl_fd("fairy_r_fly2.xpm42 was not found!", STDOUT_FILENO), false);

	xpm[DOOR] = mlx_load_xpm42("textures/moon_door.xpm42");
	if (!xpm[DOOR])
		return (ft_putendl_fd("moon_door.xpm42 was not found!", STDOUT_FILENO), false);

	xpm[STAR_MARK1] = mlx_load_xpm42("textures/star_mark1.xpm42");
	if (!xpm[STAR_MARK2])
		return (ft_putendl_fd("star_mark1.xpm42 was not found!", STDOUT_FILENO), false);

	xpm[STAR_MARK2] = mlx_load_xpm42("textures/star_mark2.xpm42");
	if (!xpm[STAR_MARK2])
		return (ft_putendl_fd("star_mark2.xpm42 was not found!", STDOUT_FILENO), false);

	xpm[STAR1] = mlx_load_xpm42("textures/star1.xpm42");
	if (!xpm[STAR1])
		return (ft_putendl_fd("star1.xpm42 was not found!", STDOUT_FILENO), false);
	
	xpm[STAR2] = mlx_load_xpm42("textures/star2.xpm42");
	if (!xpm[STAR2])
		return (ft_putendl_fd("star2.xpm42 was not found!", STDOUT_FILENO), false);

	xpm[GNOME_L_IDLE] = mlx_load_xpm42("textures/gnome_l_idle.xpm42");
	if (!xpm[GNOME_L_IDLE])
		return (ft_putendl_fd("gnome_l_idle.xpm42 was not found!", STDOUT_FILENO), false);

	xpm[GNOME_R_IDLE] = mlx_load_xpm42("textures/gnome_r_idle.xpm42");
	if (!xpm[GNOME_R_IDLE])
		return (ft_putendl_fd("gnome_r_idle.xpm42 was not found!", STDOUT_FILENO), false);

	xpm[GNOME_L_RUN] = mlx_load_xpm42("textures/gnome_l_run.xpm42");
	if (!xpm[GNOME_L_RUN])
		return (ft_putendl_fd("gnome_l_run.xpm42 was not found!", STDOUT_FILENO), false);

	xpm[GNOME_R_RUN] = mlx_load_xpm42("textures/gnome_r_run.xpm42");
	if (!xpm[GNOME_R_RUN])
		return (ft_putendl_fd("gnome_r_run.xpm42 was not found!", STDOUT_FILENO), false);

	return true;
}

bool convert_to_image(t_map *map, xpm_t **xpm, mlx_image_t **img) // converting and setting default images
{
	img[BG] = mlx_texture_to_image(map->mlx, &xpm[BG]->texture);
	img[WALL] = mlx_texture_to_image(map->mlx, &xpm[WALL]->texture);
	img[CHAR_R_FLY1] = mlx_texture_to_image(map->mlx, &xpm[CHAR_R_FLY1]->texture);
	img[DOOR] = mlx_texture_to_image(map->mlx, &xpm[DOOR]->texture);
	
	if (!img[BG] 
		|| !img[WALL] 
		|| !img[CHAR_R_FLY1]  
		|| !img[DOOR]  
		|| !img[GNOME_L_IDLE])
		return (ft_putendl_fd("Image to texture convertion has failed!", STDOUT_FILENO), false);
	
	for (int i = 0; i < MOB_COUNT; i++)
		map->mob.mob_img[i] = mlx_texture_to_image(map->mlx, &xpm[GNOME_L_IDLE]->texture);

	for (int i = 0; i < STAR_COUNT; i++)
		map->star.star_img[i] = mlx_texture_to_image(map->mlx, &xpm[STAR_MARK1]->texture);

	for (int i = 0; i < TILE_COUNT; i++)
		map->tile.tile_img[i] = mlx_texture_to_image(map->mlx, &xpm[TILE1]->texture);

	img[CHAR] = img[CHAR_R_FLY1]; //
	map->mob.type[0] = map->mob.mob_img; // ?
	map->tile.type[0] = map->tile.tile_img;
	map->star.type[0] = map->star.star_img;
	//map->mob.type[1] = NULL; // ?

	return true;
}