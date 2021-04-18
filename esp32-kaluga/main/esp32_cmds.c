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

extern void toConsole(char *msg); // TODO: move to a header file

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
    toConsole("    ");
    toConsole(de->d_name);
    toConsole("\r\n");
  }
  toConsole("\r\n");
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



//void nat_cmd_register(const char *name, const char *help, menu_func_t func, menu_access_t access);

void esp32_cmds_init(void)
{
  nat_cmd_register("ls", "list directory", cmd_ls, MENU_ACCESS);
  nat_cmd_register("cat", "show text file content", cmd_cat, MENU_ACCESS);
  nat_cmd_register("rm", "remove a file", cmd_rm, MENU_ACCESS);
  nat_cmd_register("mv", "rename a file", cmd_mv, MENU_ACCESS);
}