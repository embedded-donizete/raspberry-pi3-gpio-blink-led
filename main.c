#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <gpiod.h>

int main(int argc, char** argv) {
	struct gpiod_chip* chip;
	struct gpiod_line* line;

	chip = gpiod_chip_open("/dev/gpiochip0");
	if (!chip) {
		fprintf(stderr, "chip not found");
		goto close;
	}

	line = gpiod_chip_get_line(chip, 18);
	if (!line) {
		fprintf(stderr, "line not found");
		goto close;
	}

	if (gpiod_line_request_output(line, "gpio_output_state", 1)) {
		fprintf(stderr, "gpio_state input error");
		goto close;
	}

	int state = 1;
	while (1) {
		gpiod_line_set_value(line, state);
		printf("Changing state to %d\n", state);
		state = !state;
		sleep(1);
	}

close:
	gpiod_chip_close(chip);

	return EXIT_SUCCESS;
}
