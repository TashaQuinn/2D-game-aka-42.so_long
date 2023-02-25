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

void char_animation(mlx_key_data_t keydata, void *map)
{
	t_map *map2 = map;
	
	if (keydata.key == MLX_KEY_A)
		move_char_left(map2);
	else if (keydata.key == MLX_KEY_D)
		move_char_right(map2);
	else if (keydata.key == MLX_KEY_W)
		move_char_up(map2);
	else if (keydata.key == MLX_KEY_ESCAPE || keydata.key == MLX_KEY_Q)
		end_game();

	size_t x_char = map2->img[CHAR]->instances[0].x;
	size_t y_char = map2->img[CHAR]->instances[0].y;

	char_delete_and_put_images(map2, map2->xpm, x_char, y_char, map2->char_dir);
	
	collect_stars(map2, x_char, y_char);
}
