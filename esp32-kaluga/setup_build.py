import os
import shutil

def setup():
  if os.path.isdir("components/lvgl") == False:
    shutil.copytree("../lvgl", "./components/lvgl")
  else:
    print("lvgl already set")

if __name__ == "__main__":
  setup()

