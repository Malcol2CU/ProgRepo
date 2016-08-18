#!/usr/bin/python

import os, sys
import fnmatch as fn
import stack
import glob

class Traverse(object):
  def __init__(self, dir):
    self.dir = dir
    self.allFiles = []
    
  def walk(self, ext):
    self.allFiles = []
    dirStack = stack.Stack()
    dirStack.push( self.dir )
    while not dirStack.empty():
      currDir = dirStack.top()
      dirStack.pop()
      files = listdir_nohidden(currDir)
      for x in files:
        if fn.fnmatch(os.path.basename(x), ext+'*'):
          self.allFiles.append(x)
        if os.path.isdir(x):
          dirStack.push(x)

def listdir_nohidden(path):
    return glob.glob(os.path.join(path, '*')) 
