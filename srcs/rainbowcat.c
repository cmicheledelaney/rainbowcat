#include "rainbowcat.h"

int		width, center;

/*
** produces strings with the 256 colorcodes available.
*/
char	**get_colorcodes(void)
{
	char	**colorcodes;
	char	*code;
	int		j, pos;

	// this is the default color code. We only need to change the last
	// three digits before 'm'.
	code = "\033[01;38;5;000m";
	colorcodes = (char **)malloc(sizeof(char *) * 256);
	for (int i = 0; i < 256; i++)
	{
		colorcodes[i] = (char *)malloc(sizeof(char) * (strlen(code) + 1));
		// copies the default colorcode
		colorcodes[i] = strcpy(colorcodes[i], code);
		j = i;
		// sets the pos value to the last value before 'm'.
		pos = strlen(code) - 2;
		// the last three digits get changed so that they represent the
		// string version of 'i'.
		while (j > 0)
		{
			// the colorcode at pos gets set to the last digit of 'j'
			colorcodes[i][pos] = (char)(j % 10) + '0';
			pos--;
			j /= 10;
		}
	}
	return (colorcodes);
}

/*
** produces a sin wave for each of the base colors (red, green, blue) and
** combines them in a single value. That is done for each element of LEN.
*/
int *get_rainbow(void)
{
	int		*wave;
	int		red, grn, blu, rgb;

	wave = (int *)malloc(sizeof(int) * LEN);
	for (int i = 0; i < LEN; ++i)
	{
		red = (sin(FREQUENCY * i + PHASE1) * width + center) / 52;
		grn = (sin(FREQUENCY * i + PHASE2) * width + center) / 52;
		blu = (sin(FREQUENCY * i + PHASE3) * width + center) / 52;
		rgb = 16 + 36 * red + 6 * grn + blu;
		wave[i] = rgb;
	}
	return (wave);
}

/*
** reads the file line by line and prints it. color_codes contains all the
** 256 colorcodes, sin_wave contains a sin wave of the rgb values that
** produces a rainbow color transition.
*/
int		cat(FILE *file)
{
	char	*line;
	char	**color_codes;
	int		*sin_wave;
	size_t	size;
	int		i, up, reading;

	line = NULL;
	// gets the array of the 256 color codes
	color_codes = get_colorcodes();
	// gets the sin wave to acces the right colorcodes
	sin_wave = get_rainbow();
	i = 0;
	up = 1;
	// buff size
	size = 10;
	line = (char *)malloc(sizeof(char) * (size + 1));
	// reads file line by line
	while ((reading = getline(&line, &size, file)) != -1)
	{
		line[reading] = '\0';
		// prints each line in the according color
		printf("%s%s", color_codes[sin_wave[i]], line);
		// checks if i has reached the end or the start of the array
		// and moves in the opposite direction.
		if (up == 1)
		{
			i++;
			i == 49 ? up = 0 : 0;
		}
		else if (up == 0)
		{
			i--;
			i == 0 ? up = 1 : 0;
		}
	}
	return (0);
}

/*
** checks if the --pastel flag is on and sets the globals for
** the center and the width to the pastel values instead.
*/
int		check_colorscheme(char *colorscheme)
{
	if (strcmp(colorscheme, "--pastel") == 0)
	{
		width = WIDTH_PASTEL;
		center = CENTER_PASTEL;
		return (1);
	}
	return (0);
}

int		main(int argc, char **argv)
{
	FILE	*file;

	argv[argc] = NULL;
	// sets center and width for the sine wave to the default, which produces
	// brighter colors
	center = CENTER;
	width = WIDTH;
	// reads from stdin if there are no arguments
	if (argv[1] == NULL)
		cat(stdin);
	// iterates through the arguments
	for (int i = 1; i < argc; i++)
	{
		// checks if the --pastel flag is on an sets the values accordingly
		if (check_colorscheme(argv[i]))
			i++;
		// checks if there is an argument; if not, reads from standard input
		if (argv[i] == NULL)
		{
			cat(stdin);
			return (0);
		}
		// checks if the --help flag is on and sets the .help file as input
		if (strcmp(argv[i], "--help") == 0)
			argv[i] = ".help";
		// opens the file
		if ((file = fopen(argv[i], "r")) == NULL)
		{
			perror(argv[i]);
			continue;
		}
		// prints the file
		cat(file);
		// if there are several files it prints a newline in between
		argc > 2 && i < argc - 1 ? printf("\n") : 0;
		// closes the filedescriptor
		if (fclose(file) == -1)
		{
			perror(argv[i]);
			continue;
		}
	}
	printf("%s", RESET);
	return (0);
}
