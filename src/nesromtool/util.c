/*
 *  nesromtool/util.c
 *  nesromtool
 *
 *  Created by spike on Sat May 24 2003.
 *  Copyright (c) 2003 Sadistech. All rights reserved.
 *
 */

#include "nesromtool/util.h"

/**
 *  nes_read_header_from_file
 *  reads the header from a given FILE object into *header
 *  returns the number of bytes written which should equal NES_HEADER_SIZE
 **/
size_t
nes_read_header_from_file(FILE *ifile, nes_rom_header_t *header)
{
  char *buf = (char*)malloc(sizeof(nes_rom_header_t));

  if (fseek(ifile, NES_HEADER_OFFSET, SEEK_SET) != 0) {
    printf("error seeking\n");
    free(buf);
    return 0;
  }

  if (fread(buf, NES_HEADER_SIZE, 1, ifile) != 1) {
    printf("error reading...\n");
    free(buf);
    return 0;
  }

  memcpy(header, buf, NES_HEADER_SIZE);
  free(buf);
  return NES_HEADER_SIZE;
}

/**
 **  returns the number of PRG Banks in ifile
 **  returns 0 if an error occurrs
**/
size_t
nes_get_prg_bank_count_from_file(FILE *ifile) {

  if (fseek(ifile, NES_PRG_COUNT_OFFSET, SEEK_SET) != 0) {
    return 0;
  }

  return (size_t)fgetc(ifile);
}

/**
 **  returns the number of CHR banks in ifile
 **  returns 0 if an error occurrs
 **/
size_t
nes_get_chr_bank_count_from_file(FILE *ifile) {

  if (fseek(ifile, NES_CHR_COUNT_OFFSET, SEEK_SET) != 0) {
    return 0;
  }

  return (size_t)fgetc(ifile);
}

