#include <stdio.h>

#include "nesromtool/util.h"

int
main(int argc, char **argv, char **env)
{
  nes_rom_t *rom = (nes_rom_t*)malloc(sizeof(nes_rom_t));

  char *filename = argv[1];

  FILE *f;

  printf("reading from file: %s\n", filename);

  f = fopen(filename, "r");

  if (nes_validate_rom_file(f)) {
    printf("ROM is OK!\n");
  } else {
    printf("ROM is FUCKED\n");
    exit(EXIT_FAILURE);
  }

  if (!nes_read_rom_from_file(f, rom)) {
    printf("Unable to read rom!\n");
    return 0;
  }

  fclose(f);

  return 0;
}
