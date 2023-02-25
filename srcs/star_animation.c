#include "../includes/so_long.h"

void collect_stars(t_map *map, size_t x_char, size_t y_char)
{
	for (int star_num = 0; star_num < map->stars; star_num++)
	{
		if ((x_char >= map->star.x_star_start[star_num] && x_char <= map->star.x_star_end[star_num]) 
			&& (y_char >= map->star.y_star_start[star_num] && y_char <= map->star.y_star_end[star_num])
			&& (map->picked_up_bean[star_num] == false))
		{
			mlx_set_instance_depth(&map->star.star_img[star_num]->instances[0], -700);
			map->picked_beans_count++;
			printf("%d\n", map->picked_beans_count);
			map->picked_up_bean[star_num] = true;
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
	if (map->star_dir[star_num] == STAR1)
		map->star_dir[star_num] = STAR2;
	else
		map->star_dir[star_num] = STAR1;
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
				star_move(map, star_num);

				if (map2->picked_up_bean[star_num] == false)
					stars_delete_and_put_images(map2, map2->xpm, star_num, map2->star.x_star[star_num], map2->star.y_star[star_num], map2->star_dir[star_num]);
			}

			time = 0;
		}
	}
}