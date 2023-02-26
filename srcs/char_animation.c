#include "../includes/so_long.h"

void char_delete_and_put_images(t_map *map, xpm_t **xpm, size_t x_char, size_t y_char, t_img new_image)
{
	mlx_delete_image(map->mlx, map->img[CHAR]);
	map->img[CHAR] = mlx_texture_to_image(map->mlx, &xpm[new_image]->texture);
	mlx_image_to_window(map->mlx, map->img[CHAR], x_char, y_char);
}

void move_char_up(t_map *map)
{
	int current_char_dir = map->char_dir; // for correcting the dir while flying

	if (current_char_dir == CHAR_R_FLY1)
		map->char_dir = CHAR_R_FLY2;
	else if (current_char_dir == CHAR_R_FLY2)
		map->char_dir = CHAR_R_FLY1;
	else if (current_char_dir == CHAR_L_FLY1)
		map->char_dir = CHAR_L_FLY2;
	else if (current_char_dir == CHAR_L_FLY2)
		map->char_dir = CHAR_L_FLY1;

	map->img[CHAR]->instances[0].y -= BLOCK / CHAR_SPEED;
}

void move_char_left(t_map *map)
{
	if (map->char_dir == CHAR_L_FLY1)
		map->char_dir = CHAR_L_FLY2;
	else
		map->char_dir = CHAR_L_FLY1;

	map->img[CHAR]->instances[0].x -= BLOCK / CHAR_SPEED;
}

void move_char_right(t_map *map)
{
	if (map->char_dir == CHAR_R_FLY1)
		map->char_dir = CHAR_R_FLY2;
	else
		map->char_dir = CHAR_R_FLY1;

	map->img[CHAR]->instances[0].x += BLOCK / CHAR_SPEED;
}

void char_animation(t_map *map)
{
	if (mlx_is_key_down(map->mlx, MLX_KEY_A)) //&& (map2->coords[y_char - 1][x_char - 1] != '1'))
		move_char_left(map);
	else if (mlx_is_key_down(map->mlx, MLX_KEY_D)) //&& (x_char + 1 != '1'))
		move_char_right(map);
	else if (mlx_is_key_down(map->mlx, MLX_KEY_W)) //&& (y_char - 1 != '1'))
		move_char_up(map);
	else if ((mlx_is_key_down(map->mlx, MLX_KEY_ESCAPE) )
		|| (mlx_is_key_down(map->mlx, MLX_KEY_Q)))
		end_game();
}
