
import os, sys
import fnmatch
import stack

class Traverse(object):
  def __init__(self, dir):
    self.dir = dir
    self.files = []
    self.dirs = []
    self.cleaned = []
  def walk(self):
    dirStack = stack.Stack()
    dirStack.push( self.dir )
#    print "FULL PATH TO CURRENT DIR:", os.getcwd()
    while not dirStack.empty():
      currDir = dirStack.top()
#      print "FULL PATH TO SAMIR:", os.path.join(os.getcwd(), currDir)
      dirStack.pop()
      files = os.listdir( currDir )
      for x in files:
        path = os.path.join(currDir, x)
        if os.path.isdir(path):
 #         print "dir found:", x
          self.dirs.append(x)
          dirStack.push(path)
        else:
          if fnmatch.fnmatch(x, '*.pyc'):
            print "A .pyc:", x, ", was removed"
            os.remove(path)
            self.cleaned.append(x)
            self.cleaned.append(",")
          elif fnmatch.fnmatch(x, '*.py~'):
            print "A .py~:", x, ", was removed"
            os.remove(path)
            self.cleaned.append(x)
            self.cleaned.append(",")
          elif fnmatch.fnmatch(x, '*.c~'):
            print "A .c~:", x, ", was removed"
            os.remove(path)
            self.cleaned.append(x)
            self.cleaned.append(",")
          elif fnmatch.fnmatch(x, '*.cpp~'):
            print "A .cpp~:", x, ", was removed"
            os.remove(path)
            self.cleaned.append(x)
            self.cleaned.append(",")
          elif fnmatch.fnmatch(x, '*.h~'):
            print "A .h~:", x, ", was removed"
            os.remove(path)
            self.cleaned.append(x)
            self.cleaned.append(",")
          elif fnmatch.fnmatch(x, '*.txt~'):
            print "A .txt~:", x, ", was removed"
            os.remove(path)
            self.cleaned.append(x)
            self.cleaned.append(",")
          self.files.append(x)

if __name__ == '__main__':
  dir = None
  if len(sys.argv) == 1:
    dir = os.getcwd()
  elif len(sys.argv) == 2:
    dir = os.path.join(os.getcwd(), sys.argv[1])
  else:
    print "usage:", sys.argv[0], "{<dir>}"
    sys.exit(-1)

  print "DIR IS:", dir
  t = Traverse(dir)
  t.walk()
  print "      Files Searched:", len(t.files)
  #t.files
  print "Directories Searched:", len(t.dirs)
  #t.dirs
