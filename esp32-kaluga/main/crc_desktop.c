
#include <stdio.h>
#include "crc16.h"
#include <stdint.h>
#include <stdbool.h>

void toConsole(char * txt)
{
  printf("%s", txt);
}


int main(int argc, char *argv[])
{

  if (argc < 2) {
    toConsole("missing filename\r\n");
    return true;
  }
  int nread;
  unsigned short crc = 0;
  char fn[128];
  fn[sizeof(fn) - 1] = 0;
  //snprintf(fn, sizeof(fn) - 1, "%s%s", ROOT_PATH, args[1]);

  FILE * fh = fopen(argv[1], "rb");
  if ( ! fh) {
    toConsole("Fail\r\n");
    return true;
  }

  while ((nread = fread(fn, 1, sizeof(fn), fh)) > 0) {
    crc = crc16_ccitt_chunk(crc, fn, nread);
  }
  fclose(fh);

  sprintf(fn, "CRC16 = 0x%X\r\n", crc);
  toConsole(fn);

  return true;
}
