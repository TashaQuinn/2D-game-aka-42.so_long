#include "../includes/so_long.h"

void bat_delete_and_put_images(t_map *map, xpm_t **xpm, size_t bat_num, size_t x_bat, size_t y_bat, t_img new_image)
{
	mlx_delete_image(map->mlx, map->mob.bat_img[bat_num]);
	map->mob.bat_img[bat_num] = mlx_texture_to_image(map->mlx, &xpm[new_image]->texture);
	mlx_image_to_window(map->mlx, map->mob.bat_img[bat_num], x_bat, y_bat);
}

void witch_delete_and_put_images(t_map *map, xpm_t **xpm, size_t witch_num, size_t x_witch, size_t y_witch, t_img new_image)
{
	mlx_delete_image(map->mlx, map->mob.witch_img[witch_num]);
	map->mob.witch_img[witch_num] = mlx_texture_to_image(map->mlx, &xpm[new_image]->texture);
	mlx_image_to_window(map->mlx, map->mob.witch_img[witch_num], x_witch, y_witch);
	mlx_set_instance_depth(&map->mob.witch_img[witch_num]->instances[0], -100); // to hide the witch behind the walls when they are reached
}

void check_damage(t_map *map, size_t x_char, size_t y_char, size_t type, size_t mob_num)
{
	size_t x_mob = ((map->mob.type[type])[mob_num]->instances[0].x) / BLOCK;
	size_t y_mob = ((map->mob.type[type])[mob_num]->instances[0].y) / BLOCK;

	if (x_char == x_mob && y_char == y_mob)
	{
		map->lives--;
	}
}

static void bat_moves(t_map *map, t_mob *mob, size_t bat_num)
{	
	srand(time(NULL));

	int random = rand() % 4;

	if (bat_num % 2 == 0) // making bats move asynchronously
		random = rand() % 4;

	if ((random == 0 && mob->x_bat[bat_num] - BLOCK >= 0 + BLOCK * 2)
		|| (random == 1 && mob->y_bat[bat_num] - BLOCK <= map->height * BLOCK - BLOCK * 8))
	{
		if (map->bat_dir[bat_num] == BAT_L_FLY1)
			map->bat_dir[bat_num] = BAT_L_FLY2;
		else
			map->bat_dir[bat_num] = BAT_L_FLY1;
		
		if (random == 0)
			(map->mob.type[1])[bat_num]->instances[0].x -= HALF_BLOCK / MOB_SPEED;
		else 
			(map->mob.type[1])[bat_num]->instances[0].y += HALF_BLOCK / MOB_SPEED;
	}
	
	else if ((random == 2 && mob->x_bat[bat_num] + BLOCK <= (map->width * BLOCK) - BLOCK * 3)
		|| (random == 3 && mob->y_bat[bat_num] + BLOCK >= map->height - map->height + BLOCK * 5))
	{
		if (map->bat_dir[bat_num] == BAT_R_FLY1)
			map->bat_dir[bat_num] = BAT_R_FLY2;
		else
			map->bat_dir[bat_num] = BAT_R_FLY1;
		
		if (random == 2)
			(map->mob.type[1])[bat_num]->instances[0].x += HALF_BLOCK / MOB_SPEED;
		else 
			(map->mob.type[1])[bat_num]->instances[0].y -= HALF_BLOCK / MOB_SPEED;
	}

	else // movements when "idle" (when the random number doesn't fit movement criteria)
	{
		if (map->bat_dir[bat_num] == BAT_L_FLY1)
			map->bat_dir[bat_num] = BAT_L_FLY2;
		else if (map->bat_dir[bat_num] == BAT_L_FLY2)
			map->bat_dir[bat_num] = BAT_L_FLY1;
		else if (map->bat_dir[bat_num] == BAT_R_FLY1)
			map->bat_dir[bat_num] = BAT_R_FLY2;
		else
			map->bat_dir[bat_num] = BAT_R_FLY1;
	}
}

static void witch_moves(t_map *map, t_mob *mob, size_t witch_num)
{	
	if ((mob->x_witch[witch_num] - BLOCK >= 0) && map->witch_move_left[witch_num] == true)
	{
		if (map->witch_dir[witch_num] == WITCH_L_DOWN)
			map->witch_dir[witch_num] = WITCH_L_UP;
		else
			map->witch_dir[witch_num] = WITCH_L_DOWN;

		(map->mob.type[0])[witch_num]->instances[0].x -= BLOCK;

		if (mob->x_witch[witch_num] - BLOCK == 0)
		{
			map->witch_move_left[witch_num] = false;

			if ((mob->y_witch[witch_num] != BLOCK * 4) && (mob->y_witch[witch_num] != map->height * BLOCK - BLOCK * 8)) // changing y-axis while flying
				(map->mob.type[0])[witch_num]->instances[0].y += BLOCK;
			else
				(map->mob.type[0])[witch_num]->instances[0].y -= BLOCK * 2;
		}
	}
	
	else if ((mob->x_witch[witch_num] <= (map->width * BLOCK) - BLOCK) && map->witch_move_left[witch_num] == false)
	{	
		if (map->witch_dir[witch_num] == WITCH_R_DOWN)
			map->witch_dir[witch_num] = WITCH_R_UP;
		else
			map->witch_dir[witch_num] = WITCH_R_DOWN;
		
		(map->mob.type[0])[witch_num]->instances[0].x += BLOCK;

		if (mob->x_witch[witch_num] == (map->width * BLOCK) - BLOCK)
		{
			map->witch_move_left[witch_num] = true;
			
			if ((mob->y_witch[witch_num] != BLOCK * 4) && (mob->y_witch[witch_num] != map->height * BLOCK - BLOCK * 8))  // changing y while flying
				(map->mob.type[0])[witch_num]->instances[0].y += BLOCK;
			else
				(map->mob.type[0])[witch_num]->instances[0].y -= BLOCK * 3;
		}
	}
}

void bat_animation(t_map *map, size_t x_char, size_t y_char)
{
	static int time;
	time++;

	for (int bat_num = 0; bat_num < BATS_COUNT; bat_num++)
	{	
		if (time > 3)
		{	
			for (int bat_num = 0; bat_num < BATS_COUNT; bat_num++)
			{
				map->mob.x_bat[bat_num] = ((map->mob.type[1])[bat_num]->instances[0].x);
				map->mob.y_bat[bat_num] = ((map->mob.type[1])[bat_num]->instances[0].y);

				bat_moves(map, &map->mob, bat_num);
				check_damage(map, x_char, y_char, 1, bat_num);

				map->mob.x_bat[bat_num] = ((map->mob.type[1])[bat_num]->instances[0].x);
				map->mob.y_bat[bat_num] = ((map->mob.type[1])[bat_num]->instances[0].y);

				bat_delete_and_put_images(map, map->xpm, bat_num, map->mob.x_bat[bat_num], 
					map->mob.y_bat[bat_num], map->bat_dir[bat_num]);
			}

			time = 0;
		}
	}
}

void witch_animation(t_map *map, size_t x_char, size_t y_char)
{
	static int time;
	time++;

	for (int witch_num = 0; witch_num < WITCH_COUNT; witch_num++)
	{	
		if (time > 10)
		{	
			for (int witch_num = 0; witch_num < WITCH_COUNT; witch_num++)
			{
				map->mob.x_witch[witch_num] = ((map->mob.type[0])[witch_num]->instances[0].x);
				map->mob.y_witch[witch_num] = ((map->mob.type[0])[witch_num]->instances[0].y);

				witch_moves(map, &map->mob, witch_num);
				check_damage(map, x_char, y_char, 0, witch_num);

				map->mob.x_witch[witch_num] = ((map->mob.type[0])[witch_num]->instances[0].x);
				map->mob.y_witch[witch_num] = ((map->mob.type[0])[witch_num]->instances[0].y);

				witch_delete_and_put_images(map, map->xpm, witch_num, map->mob.x_witch[witch_num], 
					map->mob.y_witch[witch_num], map->witch_dir[witch_num]);
			}

			time = 0;
		}
	}
}

void mob_animation(t_map *map, size_t x_char, size_t y_char)
{
	bat_animation(map, x_char, y_char);
	witch_animation(map, x_char, y_char);
}
