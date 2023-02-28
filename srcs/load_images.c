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

	xpm[HEART] = mlx_load_xpm42("textures/heart.xpm42");
	if (!xpm[HEART])
		return (ft_putendl_fd("heart.xpm42 was not found!", STDOUT_FILENO), false);

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

	/*xpm[STAR_MARK1] = mlx_load_xpm42("textures/star_mark1.xpm42");
	if (!xpm[STAR_MARK2])
		return (ft_putendl_fd("star_mark1.xpm42 was not found!", STDOUT_FILENO), false);

	xpm[STAR_MARK2] = mlx_load_xpm42("textures/star_mark2.xpm42");
	if (!xpm[STAR_MARK2])
		return (ft_putendl_fd("star_mark2.xpm42 was not found!", STDOUT_FILENO), false);*/

	xpm[STAR1] = mlx_load_xpm42("textures/star1.xpm42");
	if (!xpm[STAR1])
		return (ft_putendl_fd("star1.xpm42 was not found!", STDOUT_FILENO), false);
	
	xpm[STAR2] = mlx_load_xpm42("textures/star2.xpm42");
	if (!xpm[STAR2])
		return (ft_putendl_fd("star2.xpm42 was not found!", STDOUT_FILENO), false);

	xpm[WITCH_L_DOWN] = mlx_load_xpm42("textures/witch_l_down.xpm42");
	if (!xpm[WITCH_L_DOWN])
		return (ft_putendl_fd("witch_l_down.xpm42 was not found!", STDOUT_FILENO), false);

	xpm[WITCH_R_DOWN] = mlx_load_xpm42("textures/witch_r_down.xpm42");
	if (!xpm[WITCH_R_DOWN])
		return (ft_putendl_fd("witch_r_down.xpm42 was not found!", STDOUT_FILENO), false);

	xpm[WITCH_L_UP] = mlx_load_xpm42("textures/witch_l_up.xpm42");
	if (!xpm[WITCH_L_UP])
		return (ft_putendl_fd("witch_l_up.xpm42 was not found!", STDOUT_FILENO), false);

	xpm[WITCH_R_UP] = mlx_load_xpm42("textures/witch_r_up.xpm42");
	if (!xpm[WITCH_R_UP])
		return (ft_putendl_fd("witch_r_up.xpm42 was not found!", STDOUT_FILENO), false);

	xpm[BAT_L_FLY1] = mlx_load_xpm42("textures/bat_l_fly1.xpm42");
	if (!xpm[BAT_L_FLY1])
		return (ft_putendl_fd("bat_l_fly1.xpm42 was not found!", STDOUT_FILENO), false);

	xpm[BAT_R_FLY1] = mlx_load_xpm42("textures/bat_r_fly1.xpm42");
	if (!xpm[BAT_R_FLY1])
		return (ft_putendl_fd("bat_r_fly1.xpm42 was not found!", STDOUT_FILENO), false);

	xpm[BAT_L_FLY2] = mlx_load_xpm42("textures/bat_l_fly2.xpm42");
	if (!xpm[BAT_L_FLY2])
		return (ft_putendl_fd("bat_l_fly2.xpm42 was not found!", STDOUT_FILENO), false);

	xpm[BAT_R_FLY2] = mlx_load_xpm42("textures/bat_r_fly2.xpm42");
	if (!xpm[BAT_R_FLY2])
		return (ft_putendl_fd("bat_r_fly2.xpm42 was not found!", STDOUT_FILENO), false);

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
		|| !img[DOOR])
		return (ft_putendl_fd("Image to texture convertion has failed!", STDOUT_FILENO), false);
	
	for (int i = 0; i < LIVES; i++)
		map->heart_img[i] = mlx_texture_to_image(map->mlx, &xpm[HEART]->texture);

	for (int i = 0; i < WITCH_COUNT; i++)
		map->mob.witch_img[i] = mlx_texture_to_image(map->mlx, &xpm[WITCH_L_DOWN]->texture);
	
	for (int i = 0; i < BATS_COUNT; i++)
		map->mob.bat_img[i] = mlx_texture_to_image(map->mlx, &xpm[BAT_L_FLY1]->texture);

	for (int i = 0; i < STAR_COUNT; i++)
		map->star.star_img[i] = mlx_texture_to_image(map->mlx, &xpm[STAR1]->texture); // &xpm[STAR_MARK1]->texture

	for (int i = 0; i < TILE_COUNT; i++)
		map->tile.tile_img[i] = mlx_texture_to_image(map->mlx, &xpm[TILE1]->texture);

	img[CHAR] = img[CHAR_R_FLY1];
	map->mob.type[0] = map->mob.witch_img;
	map->mob.type[1] = map->mob.bat_img;
	map->tile.type[0] = map->tile.tile_img;
	map->star.type[0] = map->star.star_img;

	map->mob.type[2] = NULL;
	map->tile.type[1] = NULL;
	map->star.type[1] = NULL;

	return true;
}