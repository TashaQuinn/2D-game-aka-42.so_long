#include "../includes/so_long.h"

void hide_tile(t_map *map, size_t x_char, size_t y_char)
{
	for (int tile_num = 0; tile_num < map->tiles; tile_num++)
	{
		if ((x_char >= map->tile.x_tile_start[tile_num] && x_char <= map->tile.x_tile_end[tile_num]) 
		&& (y_char >= map->tile.y_tile_start[tile_num] && y_char <= map->tile.y_tile_end[tile_num])
		&& (map->tile_hidden[tile_num] == false))
		{	
			int time;
			time++;
			if (time > 500)
			{
				mlx_set_instance_depth(&map->tile.tile_img[tile_num]->instances[0], -800);
				map->tile_hidden[tile_num] = true;
			}
		}
	}
}

void tiles_delete_and_put_images(t_map *map, xpm_t **xpm, int tile_num, size_t x_tile, size_t y_tile, t_img new_image)
{
	mlx_delete_image(map->mlx, map->tile.tile_img[tile_num]);
	map->tile.tile_img[tile_num] = mlx_texture_to_image(map->mlx, &xpm[new_image]->texture);
	mlx_image_to_window(map->mlx, map->tile.tile_img[tile_num], x_tile, y_tile);
	mlx_set_instance_depth(&map->tile.tile_img[tile_num]->instances[0], -400); // avoiding blocking main char
}

void tile_move(t_map *map, int tile_num)
{
	if (map->tile_mov[tile_num] == TILE1)
		map->tile_mov[tile_num] = TILE2;
	else
		map->tile_mov[tile_num] = TILE1;
}

void tile_animation(t_map *map)
{
	static int time;
	time++;

	for (int tile_num = 0; tile_num < map->tiles; tile_num++)
	{
		if (time > 70)
		{	
			for (int tile_num = 0; tile_num < map->tiles; tile_num++)
			{	
				if (tile_num % 2 == 0)
				{
					if (map->tile_hidden[tile_num] == false)
					{	
						tile_move(map, tile_num);
						tiles_delete_and_put_images(map, map->xpm, tile_num, map->tile.x_tile[tile_num], map->tile.y_tile[tile_num], map->tile_mov[tile_num]);
					}
				}
			}

			time = 0;
		}
	}
}