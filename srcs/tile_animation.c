#include "../includes/so_long.h"

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

void tile_animation(void *map)
{
	t_map *map2 = map;

	static int time;
	time++;

	for (int tile_num = 0; tile_num < map2->tiles; tile_num++)
	{
		if (time > 70)
		{	
			for (int tile_num = 0; tile_num < map2->tiles; tile_num++)
			{	
				if (tile_num % 2 == 0)
				{
					tile_move(map, tile_num);
					tiles_delete_and_put_images(map2, map2->xpm, tile_num, map2->tile.x_tile[tile_num], map2->tile.y_tile[tile_num], map2->tile_mov[tile_num]);
				}
			}

			time = 0;
		}
	}
}