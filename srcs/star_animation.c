#include "../includes/so_long.h"

void collect_stars(t_map *map, size_t x_char, size_t y_char)
{
	for (int star_num = 0; star_num < map->stars; star_num++)
	{
		if ((x_char >= map->star.x_star_start[star_num] && x_char <= map->star.x_star_end[star_num]) 
			&& (y_char >= map->star.y_star_start[star_num] && y_char <= map->star.y_star_end[star_num])
			&& (map->star_lit_up[star_num] == false))
		{
			mlx_set_instance_depth(&map->star.star_img[star_num]->instances[0], -700);
			map->lit_up_stars_count++;
			printf("%d\n", map->lit_up_stars_count); // debug
			map->star_lit_up[star_num] = true;
		}
	}
}

void stars_delete_and_put_images(t_map *map, xpm_t **xpm, int star_num, size_t x_star, size_t y_star, t_img new_image)
{
	mlx_delete_image(map->mlx, map->star.star_img[star_num]);
	map->star.star_img[star_num] = mlx_texture_to_image(map->mlx, &xpm[new_image]->texture);
	mlx_image_to_window(map->mlx, map->star.star_img[star_num], x_star, y_star);
}

void star_move(t_map *map, int star_num)
{

	if (map->star_mov[star_num] == STAR2 || map->star_mov[star_num] == STAR_MARK)
		map->star_mov[star_num] = STAR1;
	else
		map->star_mov[star_num] = STAR2;
}

void star_animation(void *map)
{
	t_map *map2 = map;

	static int time;
	time++;

	for (int star_num = 0; star_num < map2->stars; star_num++)
	{
		if (time > 30)
		{	
			for (int star_num = 0; star_num < map2->stars; star_num++)
			{	
				if (map2->star_lit_up[star_num] == true)
				{
					star_move(map, star_num);
					stars_delete_and_put_images(map2, map2->xpm, star_num, map2->star.x_star[star_num], map2->star.y_star[star_num], map2->star_mov[star_num]);
				}
			}

			time = 0;
		}
	}
}