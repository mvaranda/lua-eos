/***************************************************************
 *
 *                 This code is part of LUA_EOS
 *
 * Copyrights 2021 - Varanda Labs Inc.
 *
 * License:
 *   Creative Commons: CC BY-NC-SA 4.0
 *   Attribution-NonCommercial-ShareAlike 4.0 International
 *   https://creativecommons.org/licenses/by-nc-sa/4.0/legalcode
 *
 *   Note: for purchasing a commertial license contact:
 *     m@varanda.ca
 *
 ***************************************************************
 */

#include "eos_config.h"
#include "nat_cmd.h"
#include "esp_system.h"
#include "esp_vfs.h"
#include "esp_spiffs.h"
#include "main_defs.h"
#include "crc16.h"

extern int xmodemReceive(FILE * fh);


static bool match(const char *pattern, const char *candidate, int p, int c)
{
  if (pattern[p] == '\0') {
    return candidate[c] == '\0';
  }
  else if (pattern[p] == '*') {
    for (; candidate[c] != '\0'; c++) {
      if (match(pattern, candidate, p + 1, c))
        return true;
    }
    return match(pattern, candidate, p + 1, c);
  }
  else if (pattern[p] != '?' && pattern[p] != candidate[c]) {
    return false;
  }
  else {
    return match(pattern, candidate, p + 1, c + 1);
  }
}

static bool cmd_ls(const char *line, int num_args, const char **args)
{
  DIR *dir = opendir(ROOT_PATH);
  char buf[128];
  struct stat info;
  buf[sizeof(buf) - 1] = 0; // make sure with have a NULL terminator in case snprintf exceeds the size limit.

  bool found = false;
  while (true) {
    struct dirent *de = readdir(dir);
    if (!de) {
      break;
    }

    if (num_args > 1) { // pattern provided ?
      if (!match(args[1], de->d_name, 0, 0))
        continue;
    }

    //toConsole("    ");
    //toConsole(de->d_name);
    strcpy(buf, ROOT_PATH);
    strcat(buf, de->d_name);
    stat(buf, &info);

    snprintf(buf, sizeof(buf) - 1, "  %9d    ", (unsigned int) info.st_size);
    toConsole(buf);
    toConsole(de->d_name);
    toConsole("\r\n");
  }
  size_t total_bytes = 0, used_bytes = 0;

  if ( esp_spiffs_info(USER_PARTITION_LABLE, &total_bytes, &used_bytes) == ESP_OK) {
    snprintf(buf, sizeof(buf) - 1, "\r\n    Total size: %d, Free: %d\r\n\r\n", total_bytes, total_bytes - used_bytes);
  }
  else {
    strcpy(buf,"\r\n    Could not get FS statistics\r\n\r\n");
  }
  toConsole(buf);
  closedir(dir);

  return true;
}

static bool cmd_cat(const char *line, int num_args, const char **args)
{
  char fn[128];
  char c[2] = {0,0};
  fn[sizeof(fn) - 1] = 0;
  if (num_args < 2) {
    toConsole("missing filename\r\n");
    return true;
  }
  snprintf(fn, sizeof(fn) - 1, "%s%s", ROOT_PATH, args[1]);
  FILE * f = fopen(fn, "rb");
  if ( !f ) {
    toConsole("could not open file\r\n");
    return true;
  }
  while( (fread(c, 1, 1, f)) > 0) {
    if (c[0] > 127) {
      toConsole("?");
    }
    else {
      toConsole(c);
    }
  }
  toConsole("\r\n");
  fclose(f);

  return true;
}
// rename(name_src, name_dst) unlink
static bool cmd_rm(const char *line, int num_args, const char **args)
{
  if (num_args < 2) {
    toConsole("missing filenames\r\n");
    return true;
  }

  char fn[128];
  fn[sizeof(fn) - 1] = 0;
  snprintf(fn, sizeof(fn) - 1, "%s%s", ROOT_PATH, args[1]);

  if (unlink(fn)) {
    toConsole("Fail\r\n");
  }
  return true;
}

static bool cmd_mv(const char *line, int num_args, const char **args)
{
  if (num_args < 3) {
    toConsole("missing filenames\r\n");
    return true;
  }

  char fn[128];
  fn[sizeof(fn) - 1] = 0;
  snprintf(fn, sizeof(fn) - 1, "%s%s", ROOT_PATH, args[1]);

  char fn_dst[128];
  fn_dst[sizeof(fn_dst) - 1] = 0;
  snprintf(fn_dst, sizeof(fn_dst) - 1, "%s%s", ROOT_PATH, args[2]);


  if (rename(fn, fn_dst)) {
    toConsole("Fail\r\n");
  }
  return true;
}

static bool cmd_xload(const char *line, int num_args, const char **args)
{
  if (num_args < 2) {
    toConsole("missing filename\r\n");
    return true;
  }

  char fn[128];
  fn[sizeof(fn) - 1] = 0;
  snprintf(fn, sizeof(fn) - 1, "%s%s", ROOT_PATH, args[1]);

  FILE * fh = fopen(fn, "wb");
  if ( ! fh) {
    toConsole("Fail\r\n");
    return true;
  }

  int ret = xmodemReceive(fh);
  fclose(fh);

  if (ret > 0) {
    toConsole("OK\r\n");
  }
  else {
    sprintf(fn, "xload error %d\r\n", ret);
  }

  return true;
}

// file 28b5 crc logo_0070.jpg   here: CRC16 = 0x1B4C
static bool cmd_crc(const char *line, int num_args, const char **args)
{
  if (num_args < 2) {
    toConsole("missing filename\r\n");
    return true;
  }
  int nread;
  unsigned short crc = 0;
  char fn[128];
  fn[sizeof(fn) - 1] = 0;
  snprintf(fn, sizeof(fn) - 1, "%s%s", ROOT_PATH, args[1]);

  FILE * fh = fopen(fn, "rb");
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

#define TEMP_EXTENSION ".$$$"

static bool cmd_truncate(const char *line, int num_args, const char **args)
{
  if (num_args < 3) {
    toConsole("missing parameters. required: filename and new_size\r\n");
    return true;
  }
  int nread;
  unsigned short crc = 0;
  char fn[64];
  fn[sizeof(fn) - 1] = 0;
  snprintf(fn, sizeof(fn) - 1, "%s%s", ROOT_PATH, args[1]);

  FILE * fh = fopen(fn, "rb");
  if ( ! fh) {
    toConsole("open to read Fail\r\n");
    return true;
  }
  fseek(fh, 0 , SEEK_END);
  int len_ori = ftell(fh);
  fseek(fh, 0 , SEEK_SET);

  if (len_ori <= 0) {
    toConsole("Bad length\r\n");
    fclose(fh);
    return true;
  }
  int len_dst = atoi(args[2]);
  if (len_dst <= 0) {
    toConsole("Bad new size\r\n");
    fclose(fh);
    return true;
  }

  if (len_dst == len_ori) {
    toConsole("sizes already match\r\n");
    fclose(fh);
    return true;  
  }
  
  if (len_dst < len_ori) {
    char fn_out[64];
    fn[sizeof(fn_out) - 1] = 0;
    snprintf(fn_out, sizeof(fn_out) - 1, "%s%s%s", ROOT_PATH, args[1], TEMP_EXTENSION);


    FILE * fout = fopen(fn_out, "wb");
    if ( ! fout) {
      toConsole("Open to write fail\r\n");
      fclose(fh);
      return true;
    }

    char buf[128];
    while ( len_dst > 0) {
      int to_write = sizeof(buf);
      if (len_dst < to_write)
        to_write = len_dst;

      if (fread(buf, 1, to_write, fh) != to_write) {
        toConsole("read fail\r\n");
        fclose(fh);
        fclose(fout);
        return true;
      }
      if (fwrite(buf, 1, to_write, fout) != to_write) {
        toConsole("write fail\r\n");
        fclose(fh);
        fclose(fout);
        return true;
      }
      toConsole("read/write OK\r\n");
      len_dst -= to_write;
    }
    fclose(fh);
    fclose(fout);

    // delete original
    unlink(fn);
    if (rename(fn_out, fn)) {
      toConsole("rename fail\r\n");
    }

  }


  // while ((nread = fread(fn, 1, sizeof(fn), fh)) > 0) {
  //   crc = crc16_ccitt_chunk(crc, fn, nread);
  // }
  // fclose(fh);

  // sprintf(fn, "CRC16 = 0x%X\r\n", crc);
  // toConsole(fn);

  return true;
}


//void nat_cmd_register(const char *name, const char *help, menu_func_t func, menu_access_t access);

void esp32_cmds_init(void)
{
  nat_cmd_register("ls", "list directory", cmd_ls, MENU_ACCESS);
  nat_cmd_register("cat", "show text file content", cmd_cat, MENU_ACCESS);
  nat_cmd_register("rm", "remove a file", cmd_rm, MENU_ACCESS);
  nat_cmd_register("mv", "rename a file", cmd_mv, MENU_ACCESS);
  nat_cmd_register("xload", "receive a file via xmodem protocol", cmd_xload, MENU_ACCESS);
  nat_cmd_register("crc", "show crc16 for a file", cmd_crc, MENU_ACCESS);
  nat_cmd_register("truncate", "resize file", cmd_truncate, MENU_ACCESS);
}