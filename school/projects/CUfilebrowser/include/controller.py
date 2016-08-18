import os,sys
import Tkinter as tk
import tkMessageBox as tm
import model
import view
import subprocess as sb
import fnmatch as fn
import time

class Controller(object):
  def __init__(self, dir):
    self.model = model.Model(dir)
    self.model.setCWD()
    self.view = view.View(self)
    self.view.notify()
    self.search = False
    self.key =""
    
  def getFiles(self):
    return self.model.files
    
  def getDirs(self):
    return self.model.dirs
 
  def newFile(self):
    proc = sb.Popen(['gedit'])

  def openFile(self, event):
    listbox = event.widget
    selection = listbox.curselection()
    
    if(len(selection) > 0):
      value = listbox.get(selection[0]) 
      print value
    if os.path.isfile(value):
      exttype = self.model.fileType(value)  
      if exttype is "image":
        proc = sb.Popen(['display', value])
      elif exttype is "text":
        proc = sb.Popen(['gedit', value])
      elif exttype is "video":
        proc = sb.Popen(['vlc', value])
      elif exttype is "audio":
        proc = sb.Popen(['vlc', value])
      elif exttype is "unknown":
        result = tm.askquestion("File type", "Would you like to use Gedit?")
        if result == 'yes':
          proc = sb.Popen(['gedit', value])
        else:
            pass           
    
    else: 
      for dir in self.model.dirs:
        if os.path.basename(dir) == value:
           self.model.setCD(dir)
      self.view.notify()

  def deleteFile(self):
    selection = self.view.listbox.curselection()
    if(len(selection) > 0):
      for select in selection:
        value = self.view.listbox.get(selection[select])
        if os.path.isfile(value):
          os.remove(value)
        else:  
          tm.showerror("Error", "Is Directory, Cannot Delete")
    else:
      tm.showinfo("Notification", "Nothing to Delete")
    if not self.search: 
      self.model.setCWD()
      self.view.notify()
    else: 
      self.model.walkDir(self.key)     
      self.view.search()

  def back(self):
    self.model.setCD(os.path.normpath(os.getcwd()+os.sep+os.pardir))
    self.view.notify()
      
  def changeDir(self, event):
    value = self.view.dir.get()
    self.model.setCD(os.path.join(os.getcwd(),value))
    self.view.notify()

  def goDir(self):
      selection = self.view.listbox.curselection()
      path = self.view.listbox.get(selection[0])
      if os.path.isdir(path):self.model.setCD(path)
      else:
        path, item = os.path.split(path)
        self.model.setCD(path)
      self.view.notify()

  def cleanJunk(self):
    self.model.clean()
    if not self.search: 
      self.model.setCWD()
      self.view.notify()
    else: 
      self.model.walkDir(self.key)     
      self.view.search()
      
  def find(self, value):
    if value == "": 
      self.model.setCWD()
      self.view.notify()
      self.search = False
    else: 
      self.model.walkDir(value)     
      self.view.search()
      self.key = value
      self.search = True

  def displayP(self,event):
    listbox = event.widget
    selection = listbox.curselection()
    if(len(selection) > 0):
      value = listbox.get(selection[0])
      data ="Created: " + str(time.ctime(os.path.getctime(value)))
      data = data + " Last modified: " + str(time.ctime(os.path.getmtime(value)))
      data = data + " Size: " + str(os.path.getsize(value)) + " bytes"
      self.view.ld.set(data)
     
