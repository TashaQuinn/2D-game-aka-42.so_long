#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libs/MLX/include/MLX42/MLX42.h"
# include "../libs/libft/srcs/libft.h"

# include <sys/types.h> //
# include <stdlib.h>
# include <stdio.h> // strerror()
# include <unistd.h>
# include <fcntl.h>
# include <sys/errno.h>
# include <string.h> // strerror()

# ifndef _WIN32
	# include <sys/wait.h>
	# define WIN 0
# else 
	# include <windows.h>
	# include <mmsystem.h>
	# define WIN 1
# endif

# define BLOCK			48 // 48x28
# define HALF_BLOCK	24
# define CHAR_SPEED		5 // speed up or slow down char's movements
# define MOB_SPEED		2 // speed up or slow down mobs' movements
# define STAR_COUNT 	7 // needed for loading images
# define MOB_COUNT 		5 // needed for loading images
# define TILE_COUNT 	50 // needed for loading images
# define ACCEL 			1
# define GRAV 			1
# define ACCEL_MOD		1.2
# define JUMP_CAP		100

typedef enum s_img
{
	BG,
	WALL,
	TILE1,
	TILE2,
	CHAR, // changes its image according to the char's mov dir
	CHAR_L_FLY1,
	CHAR_R_FLY1,
	CHAR_L_FLY2,
	CHAR_R_FLY2,
	DOOR,
	STAR1,
	STAR2,
	GNOME_L_IDLE,
	GNOME_R_IDLE,
	GNOME_L_RUN,
	GNOME_R_RUN,
	IMG_COUNT,

} t_img;

typedef struct s_door
{
	size_t	x_door_start;
	size_t	y_door_end;

} t_door;

typedef struct s_tile
{
	mlx_image_t	 	*tile_img[TILE_COUNT];
	mlx_image_t	 	**type[1];
	size_t			x_tile[TILE_COUNT];
	size_t			y_tile[TILE_COUNT];

} t_tile;

typedef struct s_mob
{
	mlx_image_t	 	*mob_img[MOB_COUNT];
	mlx_image_t	 	**type[1]; // type 0 + NULL
	int				x_mob[MOB_COUNT];
	int				y_mob[MOB_COUNT];

} t_mob;

typedef struct s_star
{
	mlx_image_t	 	*star_img[STAR_COUNT];
	mlx_image_t	 	**type[1];	
	size_t			x_star[STAR_COUNT];
	size_t			y_star[STAR_COUNT];
	size_t			x_star_start[STAR_COUNT];
	size_t			y_star_start[STAR_COUNT];
	size_t			x_star_end[STAR_COUNT];
	size_t			y_star_end[STAR_COUNT];

} t_star;

typedef struct s_map
{
	void			*mlx;
	char			**map;
	int				width;
	int				height;
	//int			steps;
	t_door			door; // struct for storing door's coords
	xpm_t			*xpm[IMG_COUNT];
	mlx_image_t		*img[IMG_COUNT];

	// jump
	float			accel;
	bool			jump_lock;
	bool			fly;
	
	// tiles / clouds
	t_tile			tile; // struct for storing clouds' images
	int 			tiles; // nbr of tiles
	size_t			tile_dir[TILE_COUNT]; // movement dir for every cloudiiieee

	// char
	size_t			char_dir;
	int				lives;

	// mobs
	int 			mobs; // nbr of mobs
	t_mob			mob; // struct for storing moves' images and mobs' coords
	bool			mob_move_left[MOB_COUNT];
	size_t			mob_dir[MOB_COUNT]; // movement dir for every mob
	
	// stars
	int				stars; // nbr of stars
	t_star			star; // struct for storing moves' images and stars' coords
	size_t			star_dir[STAR_COUNT]; // movement dir for every star
	int				picked_beans_count;
	bool			picked_up_bean[STAR_COUNT]; // has the star been collected or not

} t_map;

//void	free_arr_map(t_map *map);

t_map 	*map_parsing(int argc, char **argv);
char	*get_line(char **av);
t_map	*init_map(char *line);
bool 	load_textures(xpm_t **xpm);
bool 	convert_to_image(t_map *map, xpm_t **xpm, mlx_image_t **img);
bool	display_sprites_and_steps(t_map *map);

void 	hook(void *map); // loop hook for mobs and lives left
void 	mob_animation(t_map *map, size_t x_char, size_t y_char); // iterating through all mobs, 
		// changing their movement dirs and making them run ;)
void 	gravity(t_map *map, size_t x_char, size_t y_char);
void 	end_game();

void 	tile_animation(void *map); // make our clouds move up and down to simulate hovering

void 	char_animation(mlx_key_data_t key, void *map); // key hook for a char
void 	collect_stars(t_map *map, size_t x_char, size_t y_char);

void 	star_animation(void *map); // another loop hook, but for stars this time ;) 
		// iterating through all stars, making them appear and then shiiine
void 	star_move(t_map *map, int star_num); // changing movement type (aka mov_dir)
void 	stars_delete_and_put_images(t_map *map, xpm_t **xpm, int star_num, size_t x_star, size_t y_star, t_img new_image);
		// deleting old images and replacing with new ones

void 	close_window(t_map *map, char *str);
void 	terminate(t_map *map);

#endif
