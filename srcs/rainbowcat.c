#include "rainbowcat.h"

int		width, center;

char	**get_colorcodes(void)
{
	char	**colorcodes;
	char	*code;
	int		j, pos;

	code = "\033[01;38;5;000m";
	colorcodes = (char **)malloc(sizeof(char *) * 256);
	for (int i = 0; i < 256; i++)
	{
		colorcodes[i] = (char *)malloc(sizeof(char) * (strlen(code) + 1));
		colorcodes[i] = strcpy(colorcodes[i], code);
		j = i;
		pos = strlen(code) - 2;
		while (j > 0)
		{
			colorcodes[i][pos] = (char)(j % 10) + '0';
			pos--;
			j /= 10;
		}
	}
	return (colorcodes);
}

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

int		cat(FILE *file)
{
	char	*line;
	char	**color_codes;
	int		*sin_wave;
	size_t	size;
	int		i, up, reading;

	line = NULL;
	color_codes = get_colorcodes();
	sin_wave = get_rainbow();
	i = 0;
	up = 1;
	while ((reading = getline(&line, &size, file)) != -1)
	{
		line[reading] = '\0';
		printf("%s%s", color_codes[sin_wave[i]], line);
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

int		check_colorscheme(char *colorscheme)
{
	if (strcmp(colorscheme, "--pastel") == 0)
	{
		width = WIDTH_PASTEL;
		center = CENTER_PASTEL;
		return (1);
	}
	else
	{
		width = WIDTH;
		center = CENTER;
	}
	return (0);
}

int		main(int argc, char **argv)
{
	char	*filename;
	FILE	*file;

	argv[argc] = NULL;
	if (argc < 2)
		file = stdin;
	for (int i = 1; argv[i]; i++)
	{
		if (check_colorscheme(argv[1]))
			i++;
		if (strcmp(argv[i], "--help") == 0)
			argv[i] = ".help";
		filename = argv[i];
		if ((file = fopen(filename, "r")) == NULL)
		{
			perror("rainbowcat: ");
			return (-1);
		}
		cat(file);
		argc > 2 && i < argc - 1 ? printf("\n") : 0;
		if (fclose(file) == -1)
		{
			perror("rainbowcat: ");
			return (-1);
		}
	}
	return (0);
}
