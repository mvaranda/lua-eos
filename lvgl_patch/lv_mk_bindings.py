 ###############################################################
 #
 #                 This code is part of LUA_EOS
 #
 # Copyrights 2021 - Varanda Labs Inc.
 #
 # License:
 #   Creative Commons: CC BY-NC-SA 4.0
 #   Attribution-NonCommercial-ShareAlike 4.0 International
 #   https://creativecommons.org/licenses/by-nc-sa/4.0/legalcode
 #
 #   Note: for purchasing a commertial license contact:
 #     m@varanda.ca
 #
 ###############################################################
 #

C_HEADER1 = """
#ifndef _BIND_$BASENAME$_H_
#define _BIND_$BASENAME$_H_
"""
C_HEADER2 = """
 /*
 ###############################################################
 #
 #                 This code is part of LUA_EOS
 #
 # Copyrights 2021 - Varanda Labs Inc.
 #
 # License:
 #   Creative Commons: CC BY-NC-SA 4.0
 #   Attribution-NonCommercial-ShareAlike 4.0 International
 #   https://creativecommons.org/licenses/by-nc-sa/4.0/legalcode
 #
 #   Note: for purchasing a commertial license contact:
 #     m@varanda.ca
 #
 ###############################################################
*/

#include "log.h"
#include "lua_eos.h"
#include "lvgl.h"
#include "lauxlib.h"
#include "$BASENAME$.h"

#ifdef __cplusplus
extern "C" {
#endif

"""

END_C = """

#ifdef __cplusplus
  }
#endif
"""

LUA_BODY = """
-- ***************************************************************
-- *
-- *                 This code is part of LUA_EOS
-- *
-- * Copyrights 2021 - Varanda Labs Inc.
-- *
-- * License:
-- *   Creative Commons: CC BY-NC-SA 4.0
-- *   Attribution-NonCommercial-ShareAlike 4.0 International
-- *   https://creativecommons.org/licenses/by-nc-sa/4.0/legalcode
-- *
-- *   Note: for purchasing a commertial license contact:
-- *     m@varanda.ca
-- *
-- ***************************************************************

-- Enumerations

-- Load module
  lv.$BASENAME$__init_module()

"""

ENDL = "\n"

MODULE_INIT = """
int bind_$BASENAME$__init_module(lua_State *L)
{
  $BASENAME$__init();

  return 0;
}
"""

FUNC_DEF = """
static int bind_$FUNC_NAME$(lua_State *L)
{
"""

PAR_OBJ = "  void * $PAR_NAME$ = lua_touserdata(L,$PAR_N$);"

PAR_INT = "  int $PAR_NAME$ = lua_tointeger(L,$PAR_N$);"
  
PAR_BOOL = "  int $PAR_NAME$ = lua_toboolean(L,$PAR_N$);"

PAR_STRING = "  const char * $PAR_NAME$ = lua_tostring(L,$PAR_N$);"

RET_VOID = """
  return 0;
}
"""

RET_OBJ = """
  if (! ret) {
    lua_pushnil(L);
  }
  else {
    lua_pushlightuserdata(L, ret);
  }
  return 1;
}
"""

RET_INT = """
  lua_pushinteger(L, ret);
  return 1;
}
"""

RET_BOOL = """
  lua_pushboolean(L, ret);
  return 1;
}
"""

RET_STRING = """
  lua_pushstring(L, ret);
  return 1;
}
"""

BIND_LIST_DEF_FUNC = "int bind_$BASENAME$__init_module(lua_State *L)"

  
BIND_REG_TABLE = """
  { NULL, NULL},
};

void bind_init_lvgl_modules(lua_State *L)
{
  lv_append_lib_funcs(L, binding_names);
}
"""

BIND_TABLE = """
static const luaL_Reg binding_names [] = {
"""


BIND_LIST_DEF = """
  { NULL, NULL},
};

void lv_append_lib_funcs(lua_State *L, luaL_Reg reg[]);

int bind_$BASENAME$__init_module(lua_State *L)
{
  lv_append_lib_funcs(L, binding_names);
  return 0;
}
"""
  
BIND_LIST_ENTRY = "  { \"$LUA_FUNC_NAME$\", bind_$FUNC_NAME$ },"

  
INIT_ALL = """
void bind_init_lvgl_modules(lua_State *L)
{
"""
  
INIT_ALL_ENTRY = "  {\"$BASENAME$__init_module\", bind_$BASENAME$__init_module}," + ENDL


import sys, os

VERSION = "0.01"

object_functions = {}

root_dirs = {
  "../lvgl/src"
  }

exclude_dirs = {
  "../lvgl/src/lv_gpu"
}
  

def create_file_list():
  files = []
  for rootDir in root_dirs:
    #print("rootDir = " + rootDir)
    for dirName, subdirList, fileList in os.walk(rootDir):
      if dirName.endswith('/') == False:
        dirName = dirName + '/'
      exclude = False
      #print("dirName = " + dirName)
      for e in exclude_dirs:
        if dirName.startswith(e) == True:
          exclude = True
          break
      if exclude == True:
        continue
      for fname in fileList:
        fullname = dirName + fname
        
        if fname.startswith('lv_') and fname.endswith('.h'):
          fullname = dirName + fname
          files.append(fullname)
  return files

# out = read_removing_comments('../lvgl/src/lv_core/lv_obj.h')
def read_removing_comments(filename):
  out = ""
  f = open(filename)
  comment_state = False
  while True:
    l = f.readline()
    if len(l) == 0:
      f.close()
      break
    if comment_state == False:
      i = l.find("/*")
      if i>=0:
        out = out + l[:i]
        comment_state = True
        continue
      i = l.find("//")
      if i>=0:
        out = out + l[:i]
        continue
      out = out + l
      
    else: # in comment state
      i = l.find("*/")
      if i >=0:
        out = out + l[i+2:]
        comment_state = False
  f.close()
  return out

# r = parse_obj_function(DEFAULT_FILENAME)

# return err_txt, func_dic
def parse_function(line):
  print("function: " + line)
  ret = None
  dic = {}

#example:
# void lv_obj_init_draw_line_dsc(lv_obj_t * obj, uint8_t part, lv_draw_line_dsc_t * draw_dsc);
# {'name': 'lv_obj_init_draw_line_dsc', 'ret': 'void', 'num_params': 3, 'params': [{'type': 'lv_obj_t *', 'name': 'obj'}, {'type': 'uint8_t', 'name': 'part'}, {'type': 'lv_draw_line_dsc_t *', 'name': 'draw_dsc'}]}

  try:
    l_r = line.split("(")
    l = l_r[0].split()
    func_name = l[len(l) - 1]
    print("function name: " + func_name)
    dic["name"] = func_name
    dic["ret"] = " ".join(l[0:len(l) - 1])
    
    #params
    p = l_r[1].replace(';','')
    p = p.replace(')','')
    p = p.split(',')
    dic["num_params"] = len(p)
    params = []
    for pp in p:
      p_dic = {}
      pp_s = pp.split()
      p_dic["type"] = " ".join(pp_s[0:len(pp_s) - 1])
      p_dic["name"] = pp_s[len(pp_s) - 1]
      params.append(p_dic)
    dic["params"] = params
      

  except:
    return "\n\nFail to parse: " + line + "\n\n", None
  return None, dic


def parse_obj_functions(filename):
  content = read_removing_comments(filename)
  lines = content.split('\n')
  funcs = []
  l = ""
  l_num = 1
  is_macro = False
  for line in lines:
    if l == "":
      print("line " + str(l_num) + ":")
      l_num = l_num + 1
      if line.find("(") < 0:
        continue
      if line.find("typedef") >= 0:
        continue
      if line.find("#") >= 0:
        continue        
    l = l + line
    
    #if found_function == True: # pending ";"
    if l.find(";") >= 0:
      [err, f_dic] = parse_function(l)
      if err == None:
        funcs.append([f_dic, l])
      else:
        print(err)
      l = ""
  return funcs

def append_function(bind_array, c_file, ch_file, f):
  # {'name': 'lv_obj_init_draw_line_dsc', 'ret': 'void', 'num_params': 3, 'params': [{'type': 'lv_obj_t *', 'name': 'obj'}, {'type': 'uint8_t', 'name': 'part'}, {'type': 'lv_draw_line_dsc_t *', 'name': 'draw_dsc'}]}

  c_file.write("// ***********************************************" + ENDL) 
  c_file.write("// * " + f[1] + ENDL)
  c_file.write("// ***********************************************" + ENDL)
  c_file.write(FUNC_DEF.replace("$FUNC_NAME$", f[0]["name"]))
  #ch_file.write("// " + f[1] + ENDL)
  p_n = 1
  
  #print(f[0])
  # create parameters
  fcall_params = "("
  for p in f[0]["params"]:
    if p["name"] == "void":
      fcall_params = fcall_params + ");"
      c_file.write(ENDL + "  UNUSED(L);" + ENDL)
      continue
    elif p["type"].find("char *") >= 0:
      l = PAR_STRING.replace("$PAR_NAME$", p["name"])
    elif p["type"] == "bool":
      l = PAR_BOOL.replace("$PAR_NAME$", p["name"])  
    # if type has * then assume user defined obj
    elif p["type"].find('*') >= 0:
      l = PAR_OBJ.replace("$PAR_NAME$", p["name"])
    else:
      l = PAR_INT.replace("$PAR_NAME$", p["name"])  
    l = l.replace("$PAR_N$", str(p_n))
    c_file.write(l + ENDL)
    fcall_params = fcall_params + p["name"] + ", "
    p_n = p_n +1
  c_file.write(ENDL)
  fcall_params = fcall_params[0:len(fcall_params) - 2]
  fcall_params = fcall_params + ");"
  
  # create the function call
  if f[0]["ret"].find("void") >= 0:
    fcall = "  " + f[0]["name"] + fcall_params + ENDL
  else:
    fcall = "  " + f[0]["ret"] + " ret = " + f[0]["name"] + fcall_params + ENDL
  fcall = fcall.replace("static inline ", '')
  c_file.write(fcall)
  
  # create return
  if f[0]["ret"].find("void") >= 0:
    c_file.write(RET_VOID)
  elif f[0]["ret"].find("bool") >= 0:
    c_file.write(RET_BOOL)
  elif f[0]["ret"].find("char *") >= 0:
    c_file.write(RET_STRING)
  elif f[0]["ret"].find("*") >= 0:
    c_file.write(RET_OBJ)
  else:
    c_file.write(RET_INT)
  c_file.write(ENDL + ENDL)
  
  e = BIND_LIST_ENTRY.replace("$FUNC_NAME$", f[0]["name"])
  #bind_array = bind_array + BIND_LIST_ENTRY.replace("$FUNC_NAME$", f[0]["name"])
  bind_array = bind_array + e.replace("$LUA_FUNC_NAME$", f[0]["name"][3:]) + ENDL
  return bind_array
  
  

def mk():
  files = create_file_list()
  #files = ['style_expanded.h']
  if len(files) == 0:
    print("no header file found")
    return
  
  #files = [ '../lvgl/src/lv_core/lv_obj.h' ]
  includes = ""
  init_all = BIND_TABLE
  for file in files:
    print("processing file: " + file)
    base_name = file.split('/')
    base_name = base_name[len(base_name)-1]
    base_name = base_name.replace('.h','')
    print("base_name = " + base_name)
    funcs = parse_obj_functions(file)
    #print(funcs)
    c_file = open("bind_" + base_name + ".c", 'w')
    c_file.write(C_HEADER2.replace("$BASENAME$", base_name))
    c_file.write(ENDL + "#define UNUSED(x) (void)(x)" + ENDL)
    ch_file = open("bind_" + base_name + ".h", 'w')
    includes = includes + "#include \"" + "bind_" + base_name + ".h\"" + ENDL
    ch_file.write(C_HEADER1.replace("$BASENAME$", base_name))
    ch_file.write(C_HEADER2.replace("$BASENAME$", base_name))
    ch_file.write(ENDL + BIND_LIST_DEF_FUNC.replace("$BASENAME$", base_name) + ";"  + ENDL)
    #init_all = init_all + "  bind_" + base_name + "__init_module(L);" + ENDL
    init_all = init_all + INIT_ALL_ENTRY.replace("$BASENAME$", base_name)
    ch_file.write(ENDL + "// --------------------------------------------------" + ENDL)
    ch_file.write("#endif" + ENDL)
                  
    #bind_array = BIND_LIST_DEF.replace("$BASENAME$", base_name)
    bind_array = BIND_TABLE
    for f in funcs:
      if f[0]["name"].find("_lv_") == 0: #disregard locals
        continue
      if f[0]["name"].find("LV_") == 0: #disregard macros
        continue
      bind_array = append_function(bind_array, c_file, ch_file, f)
  
    bind_array = bind_array + BIND_LIST_DEF.replace("$BASENAME$", base_name)
    c_file.write(bind_array)
    print(bind_array)
  
    lua_file = open(base_name + ".lua", 'w')
    lua_file.write(LUA_BODY.replace("$BASENAME$", base_name))
    lua_file.close()
  
    init_file = open("lvgl_init_modules.c", 'w')
    init_file.write(C_HEADER2.replace("$BASENAME$", base_name))
    init_file.write(includes)
    init_file.write(init_all)
    init_file.write(BIND_REG_TABLE)
    init_file.write(END_C)
    init_file.close()
    
    c_file.write(END_C)
    ch_file.write(END_C)
    c_file.close()
    ch_file.close()
  
if __name__ == "__main__":
  print("lv_mkbindings version %s\n" % VERSION)
  mk()
  
#  if len(sys.argv) <= 1:
#    input_file = DEFAULT_FILENAME
#  else:
#    input_file = sys.argv[1]
#  print("input file \"" + filename + "\"")

  