#!/usr/bin/python

import sys
import os
import include.controller
import Tkinter as tk

if __name__ == "__main__":
  dir = None
  if len(sys.argv) == 1:
    dir = os.getcwd()
  elif len(sys.argv) == 2:
    dir = os.path.join(os.getcwd(), sys.argv[1])
  else:
    print "usage:", sys.argv[0], "{<dir>}"
    sys.exit(-1)
  
  con = include.controller.Controller(dir)
  tk.mainloop()
