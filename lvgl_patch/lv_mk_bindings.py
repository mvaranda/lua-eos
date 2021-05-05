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

"""
L_HEADER = """
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

"""

FUNC_DEF = """
static int $FUNC_NAME$(lua_State *L)
"""

PAR_OBJ = """
  void * $PAR_N$ = lua_touserdata(L,$PAR_N$);
"""

PAR_INT = """
  int $PAR_N$ = lua_tointeger(L,$PAR_N$);
"""

PAR_STRING = """
  const char * $PAR_N$ = lua_tostring(L,$PAR_N$);
"""

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
  lua_pushinteger(L, ret)
  return 1
}
"""

RET_INT = """
  lua_pushstrinf(L, ret)
  return 1
}
"""

BIND_LIST_DEF = """
void $BASENAME$_init(lua_State *L)
{
"""
import sys, os

VERSION = "0.01"

object_functions = {}

root_dirs = {
  "../lvgl/src"
  }

exclude_dirs = {
  "../lvgl/src/lv_gpu"
}
  
ENDL = "\n"

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
  c_file.write("// " + f[1] + ENDL)
  ch_file.write("// " + f[1] + ENDL)
  

def mk():
  files = create_file_list()
  if len(files) == 0:
    print("no header file found")
    return
  
  files = [ '../lvgl/src/lv_core/lv_obj.h' ]
  for file in files:
    print("processing file: " + file)
    base_name = file.split('/')
    base_name = base_name[len(base_name)-1]
    base_name = base_name.replace('.h','')
    print("base_name = " + base_name)
    funcs = parse_obj_functions(file)
    #print(funcs)
    c_file = open("bind_" + base_name + ".c", 'w')
    c_file.write(C_HEADER2)
    ch_file = open("bind_" + base_name + ".h", 'w')
    ch_file.write(C_HEADER1.replace("$BASENAME$", base_name))
    ch_file.write(C_HEADER2)
                  
    bind_array = BIND_LIST_DEF
    bind_array.replace("$BASENAME$", base_name)
    for f in funcs:           
      bind_array = append_function(bind_array, c_file, ch_file, f)
                  
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

  