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

size_t
nes_get_prg_bank_offset(FILE *ifile, int bank_index, nes_rom_header_t *header)
{
  return (NES_HEADER_OFFSET + NES_HEADER_SIZE + ( bank_index * NES_PRG_BANK_LENGTH ));
}

size_t
nes_get_chr_bank_offset(FILE *ifile, int bank_index, nes_rom_header_t *header)
{
  int prg_count;

  if (header) {
    prg_count = header->prg_count;
  } else {
    prg_count = nes_get_prg_bank_count_from_file(ifile);
  }

  return (NES_HEADER_OFFSET                           // baseline
          + NES_HEADER_SIZE                           // + header size
          + ((prg_count + 1) * NES_PRG_BANK_LENGTH)   // size of all PRG banks combined
          + (bank_index * NES_CHR_BANK_LENGTH));      // shift forward bank_index CHR banks
}

size_t
nes_read_prg_bank_from_file(FILE *ifile, int bank_index, nes_rom_header_t *header, char *buf)
{
  size_t prg_bank_offset = nes_get_prg_bank_offset(ifile, bank_index, header);

  // FIXME: this should detect errors, etc
  fseek(ifile, prg_bank_offset, SEEK_SET);

  return fread(buf, NES_PRG_BANK_LENGTH, 1, ifile);
}

size_t
nes_read_chr_bank_from_file(FILE *ifile, int bank_index, nes_rom_header_t *header, char *buf)
{
  size_t chr_bank_offset = nes_get_chr_bank_offset(ifile, bank_index, header);

  // FIXME: this should detect errors, etc
  fseek(ifile, chr_bank_offset, SEEK_SET);

  return fread(buf, NES_CHR_BANK_LENGTH, 1, ifile);
}

size_t
nes_read_rom_from_file(FILE *ifile, nes_rom_t *rom)
{
  rom->header = (nes_rom_header_t *)malloc(sizeof(nes_rom_header_t));
  rom->prg_banks = g_slist_alloc();
  rom->chr_banks = g_slist_alloc();

  int i = 0;

  // first, read the header in
  if (nes_read_header_from_file(ifile, rom->header) != NES_HEADER_SIZE) {
    printf("error reading header from file\n");
    return 0;
  }
  // then read each prg bank
  char *prg_buf;
  for (i = 0; i < rom->header->prg_count; i++) {
    prg_buf = (char*)malloc(NES_PRG_BANK_LENGTH);
    nes_read_prg_bank_from_file(ifile, i, rom->header, prg_buf);
    rom->prg_banks = g_slist_append(rom->prg_banks, prg_buf);
  }

  // then read each chr bank
  char *chr_buf;
  for (i = 0; i < rom->header->chr_count; i++) {
    chr_buf = (char*)malloc(NES_CHR_BANK_LENGTH);
    nes_read_chr_bank_from_file(ifile, i, rom->header, chr_buf);
    rom->chr_banks = g_slist_append(rom->chr_banks, chr_buf);
  }

  // then read the title
  return 1;
}

