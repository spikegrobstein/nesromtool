#include <stdio.h>

#include "nesromtool/util.h"

int
main(int argc, char **argv, char **env)
{
  nes_rom_header_t *header = (nes_rom_header_t*)malloc(sizeof(nes_rom_header_t));

  char *filename = argv[1];

  FILE *f;

  printf("reading from file: %s\n", filename);

  f = fopen(filename, "r");

  if (nes_read_header_from_file(f, header) != NES_HEADER_SIZE) {
    printf("Unable to read header!\n");
    return 0;
  }

  fclose(f);

  return 0;
}
