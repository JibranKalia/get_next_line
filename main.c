
#include "get_next_line.h"
#include "ft_ansi.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

void	test_basic(void)
{
	size_t	line_count;
	char	*line;
	int		fd;

	line_count = 0;
	line = NULL;
	printf("Opening file... ");
	fd = open("test_basic_dino.txt", O_RDONLY);
	if (fd < 0)
	{
		printf("Error opening %s.\n", "test_basic_dino.txt");
		return;
	}
	printf("Done.\n");
	printf("Reading Lines...\n");
	while (get_next_line(fd, &line) > 0 && line_count < 20)
	{
		line_count++;
		printf(ANSI_F_CYAN "%zu" ANSI_RESET "\t|%s" ANSI_F_CYAN "$\n" ANSI_RESET, line_count, line);
		printf("Main Free\n");
		free(line);
	}
	if (line_count != 12)
		printf("ERROR: test_basic(...) failed.\n");
	else
		printf("Done.\n");	
	printf("[ Lines Expected: 12, Lines Read: %zu ]\n", line_count);
	fd = close(fd);
	if (fd < 0)
	{
		printf("Fatal Error: Could not close open file.\n");
		exit(EXIT_FAILURE);
	}
}

int				simple_test(void)
{
	char		*line;
	int			fd;
	int			count_lines;
	char		*filename;
	int			errors;

	filename = "gnl7_3.txt";
	fd = open(filename, O_RDONLY);
	if (fd > 2)
	{
		count_lines = 0;
		errors = 0;
		line = NULL;
		while (get_next_line(fd, &line) > 0)
		{
			if (count_lines == 0 && strcmp(line, "1234567") != 0)
				errors++;
			if (count_lines == 1 && strcmp(line, "abcdefg") != 0)
				errors++;
			if (count_lines == 2 && strcmp(line, "4567890") != 0)
				errors++;
			if (count_lines == 3 && strcmp(line, "defghijk") != 0)
				errors++;
			count_lines++;
			printf("MAIN %d = %s\n", count_lines, line);
			printf("Main Free\n");
			free(line);
			if (count_lines > 50)
				break ;
		}
		close(fd);
		if (count_lines != 4)
			printf("-> should have returned '1' four times instead of %d time(s)\n", count_lines);
		if (errors > 0)
			printf("-> should have read \"1234567\", \"abcdefg\", \"4567890\" and \"defghijk\"\n");
		if (count_lines == 4 && errors == 0)
			printf("OK\n");
	}
	else
		printf("An error occured while opening file %s\n", filename);
	return (0);
}

void	test_poems(void)
{
	size_t	line_count;
	char	*line;
	int		fd_i;
	int		fd_a;
	int		fd_b;

	line = NULL;
	line_count = 0;
	fd_i = open("timmy_test_interleave.txt", O_RDONLY);
	fd_a = open("timmy_test_a.txt", O_RDONLY);
	fd_b = open("timmy_test_b.txt", O_RDONLY);
	if (fd_i < 0 || fd_a < 0 || fd_b < 0)
	{
		printf(ANSI_F_RED "Error opening files.\n" ANSI_RESET);
		return ;
	}
	printf(ANSI_F_YELLOW "Starting interleaved file read test...\n\n" ANSI_RESET);
	line_count = 0;
	while (line_count < 4)
	{
		line_count++;
		get_next_line(fd_i, &line);
		printf(ANSI_F_CYAN "%zu" ANSI_RESET "\t|%s" ANSI_F_CYAN "$\n" ANSI_RESET, line_count, line);
		printf("Main Free\n");
		free(line);
	}
	while (get_next_line(fd_a, &line) > 0)
	{
		line_count++;
		printf(ANSI_F_CYAN "%zu" ANSI_RESET "\t|%s" ANSI_F_CYAN "$\n" ANSI_RESET, line_count, line);
		printf("Main Free\n");
		free(line);
	}
	line_count++;
	get_next_line(fd_i, &line);
	printf(ANSI_F_CYAN "%zu" ANSI_RESET "\t|%s" ANSI_F_CYAN "$\n" ANSI_RESET, line_count, line);
	free(line);
	while (get_next_line(fd_b, &line) > 0)
	{
		line_count++;
		printf(ANSI_F_CYAN "%zu" ANSI_RESET "\t|%s" ANSI_F_CYAN "$\n" ANSI_RESET, line_count, line);
		printf("Main Free\n");
		free(line);
	}
	while (get_next_line(fd_i, &line) > 0)
	{
		line_count++;
		printf(ANSI_F_CYAN "%zu" ANSI_RESET "\t|%s" ANSI_F_CYAN "$\n" ANSI_RESET, line_count, line);
		printf("Main Free\n");
		free(line);
	}
	if (line_count != 45)
		printf(ANSI_F_RED "\nERROR: Interleaved files test failed! [ test_poems(...); ]\n" ANSI_RESET);
	else
		printf(ANSI_F_GREEN "\nDone.\n" ANSI_RESET);
	printf(ANSI_F_YELLOW "[ Lines Expected: 45, Lines Read: %zu ]\n" ANSI_RESET, line_count);
	fd_i = close(fd_i);
	fd_a = close(fd_a);
	fd_b = close(fd_b);
	if (fd_i < 0 || fd_a < 0 || fd_b < 0)
	{
		printf(ANSI_F_BRED "Fatal Error: Could not close open files!\n" ANSI_RESET);
		exit(EXIT_FAILURE);
	}
}

static void simple_string()
{
	char 	*line;
	int		out;
	int		p[2];
	int		fd;
	int		gnl_ret;

	out = dup(1);
	pipe(p);

	fd = 1;
	dup2(p[1], fd);
	write(fd, "abc\n\n", 5);
	close(p[1]);
	dup2(out, fd);

	/* Read abc and new line */
	gnl_ret = get_next_line(p[0], &line);
	if (gnl_ret == 1)
		printf("Fine1\n");
	else
		printf("Error\n");

	if (strcmp(line, "abc") == 0)
		printf("Fine2\n");
	else
		printf("Error\n");

	/* Read new line */
	gnl_ret = get_next_line(p[0], &line);
	if (gnl_ret == 1)
		printf("Fine3\n");
	else
		printf("Error\n");

	if (line == NULL || *line == '\0')
		printf("Fine4\n");
	else
		printf("Error\n");

	/* Read again, but meet EOF */
	gnl_ret = get_next_line(p[0], &line);
	
	if (gnl_ret == 0)
		printf("Fine5\n");
	else
		printf("Error\n");

	if (line == NULL || *line == '\0')
		printf("Fine6\n");
	else
		printf("Error\n");

	gnl_ret = get_next_line(p[0], &line);
	if (gnl_ret == 0)
		printf("Fine7\n");
	else
		printf("Error\n");

	if (line == NULL || *line == '\0')
		printf("Fine8\n");
	else
		printf("Error\n");
}

int		main(void)
{
	//test_basic();
	//simple_test();
	test_poems();
	simple_string();
	return (0);
}
