import sys, os
import fnmatch as fn
import Tkinter as tk
import tkMessageBox as tm
import traverse 
import glob
import clean
import stack

cases = ['*.*~', '.*', '*~']
images = ['*.gif', '*.png', '*.ppm', '*.jpg']
textfs = ['*.txt', '*.ini', '*.cpp', '*.c', '*.java',\
          '*.ml', '*.bat', '*.h', '*.exe','*.pro','*.py']
video = ['*.mp4','*.MOV','*.mov','*.flv','*.avi',\
         '*.wmv','*.m4p','*.mpg','*.mpeg', '*.m4v']
audio = ['*.mp3','*.wav','*.m4a','*.wma','*.aac']

class Model(object):
  def __init__(self,dir):
    self.t = traverse.Traverse(dir)
    self.currD = dir
    self.files = []
    self.dirs = []
    self.allFiles = []

  def setCD(self, dir):
    os.chdir(dir)
    self.currD = os.getcwd()
    self.t.dir = os.getcwd()
    self.setCWD()
 
  def setCWD(self):
    allFiles = listdir_nohidden(self.currD)
    self.splitFiles(allFiles)
  
  def getIndex(self, value):
    for dirs in self.allFiles:
       if os.path.basename(dirs) == value:return dirs  
 
  def clean(self):
      c = clean.Traverse(self.currD)
      c.walk()
      if (len(c.cleaned) > 0 ):
          tm.showinfo("Files Removed!", c.cleaned) 
      else:
          tm.showinfo("Directories Clean!", "System Clean, No Files to Remove.")
  def walkDir(self, ext):
      self.t.walk(ext)
      allFiles = self.t.allFiles
      self.splitFiles(allFiles)

  def splitFiles(self, allFiles):
    self.files = []
    self.dirs = []
    for case in cases:
      [allFiles.remove(x) for x in allFiles if fn.fnmatch(x,case)]
    [self.files.append(file) for file in allFiles if os.path.isfile(file)]
    [self.dirs.append(file) for file in allFiles if os.path.isdir(file)]
    self.allFiles = allFiles
           
  def fileType(self, extension):
      for x in images:
          if fn.fnmatch(extension, x):
              return "image"
      for x in textfs:
          if fn.fnmatch(extension, x):
              return "text"
      for x in video:
          if fn.fnmatch(extension,x):
              return "video"
      for x in audio:
          if fn.fnmatch(extension, x):
              return "audio"
      return "unknown"
   
def listdir_nohidden(path):
    return glob.glob(os.path.join(path, '*'))
      
if __name__ == '__main__':
  m = Model(os.getcwd())
  m.walkDir('.pyc')

