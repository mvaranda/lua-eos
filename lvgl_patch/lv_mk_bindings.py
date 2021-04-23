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

import sys
import json

VERSION = "0.01"
DEFAULT_FILENAME = "lv_objts.json"

object_functions = {}

# out = read_removing_comments('/Users/mvaranda/lua-eos/lvgl/src/lv_core/lv_obj.h')
def read_removing_comments(filename):
  out = ""
  f = open(filename)
  comment_state = False
  while True:
    l = f.readline()
    print('readline')
    if len(l) == 0:
      print('line empty')
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

def parse_obj_function(filename):
  print("parsing object_functions...")
  f = open(filename)
  j = json.load(f)
  
  for obj in j['objects']:
    print("  obj: " + str(obj))
    for member in obj['members']:
      print(member)
      #print("  member: " + str(member))
  return j
  

if __name__ == "__main__":
  print("lv_mkbindings version %s\n" % VERSION)
  if len(sys.argv) <= 1:
    input_file = DEFAULT_FILENAME
  else:
    input_file = sys.argv[1]
  print("input file \"" + filename + "\"")
  
  parse_obj_function(input_file)
  
    
for obj in j['objects'].items():
  for m in obj.items():
    print(m)




def iterate_multidimensional(my_dict, level):
    for k,v in my_dict.items():
        for i in range(level * 2):
            print(" ", end = "")      if(isinstance(v,dict)):
        print(k+":")
            level = level + 1
            iterate_multidimensional(v, level)
            continue
        print(k+" : "+str(v))
        
def iterate_multidimensional(my_dict, level):
    for k,v in my_dict.items():
        for i in range(level * 2):
            print(" ", end = "")
        if(isinstance(v,dict)):
            print(k+":")
            level = level + 1
            iterate_multidimensional(v, level)
            continue
        print(k+" : "+str(v))

