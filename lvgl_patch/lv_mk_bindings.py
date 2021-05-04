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

#a = {"name" : "myfunc", "num_params": 5, "params" : [ {"type" : "char", "varname" : "buf"} ] }
#print(a)
#{'name': 'myfunc', 'num_params': 5, 'params': [{'type': 'char', 'varname': 'buf'}]}
#b = {"name" : "myfuncB", "num_params": 2, "params" : [ {"type" : "char", "varname" : "buf"} ] }
#f = [a,b]
#print(f[1])
#{'name': 'myfuncB', 'num_params': 2, 'params': [{'type': 'char', 'varname': 'buf'}]}
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
  print(dic)
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
        funcs.append(f_dic)
      else:
        print(err)
      l = ""
  

def mk():
  files = create_file_list()
  if len(files) == 0:
    print("no header file found")
    return
  
  files = [ '../lvgl/src/lv_core/lv_obj.h' ]
  for file in files:
    parse_obj_functions(file)
  
if __name__ == "__main__":
  print("lv_mkbindings version %s\n" % VERSION)
  mk()
  
#  if len(sys.argv) <= 1:
#    input_file = DEFAULT_FILENAME
#  else:
#    input_file = sys.argv[1]
#  print("input file \"" + filename + "\"")

  