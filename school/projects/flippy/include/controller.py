import os,sys
import Tkinter as tk
import tkMessageBox as tm
import model 
import view
import subprocess as sb
import fnmatch as fn

from PIL import ImageTk
import tkFileDialog
import time

class Controller(object):
  def __init__(self, dir):
    self.model = model.Model(dir)
    self.view = view.View(self)
    self.Stop = False
    self.frame = 0
    self.len = len(self.model.flipImg)
    self.loop = False
    self.fast = False
    self.view.thread2()
    self.view.thread()
    

  def saveXMLData(self):
    self.model.saveSettings()

  def percent(self, percent):
    print "resizing the picture with convert <image> -resize <", percent, "%> <newimage>"

  def transpose(self, effect):
    print "transpose the picture with convert <image> ", effect, "new image"

  def stepLt(self):
    if self.frame != 0: 
      self.view.display(self.model.flipImg[self.frame],float(self.model.dRate))
      self.view.progBar.step(-(float(100)/self.len))
      self.frame = self.frame - 1
    
  def stepRt(self):
    if self.frame == self.len: self.frame = 0
    self.view.display(self.model.flipImg[self.frame], float(self.model.dRate))
    self.view.progBar.step(float(100)/self.len)
    self.frame = self.frame + 1

  def load(self):
    while self.frame > 0:
       self.view.progBar.step(-(float(100)/self.len))
       self.frame = self.frame - 1   
    dirname = tkFileDialog.askdirectory()
    self.model.loadImages(dirname)
    self.display()

  def display(self):
    self.view.display(self.model.flipImg[0], self.model.dRate) 
    self.len = len(self.model.flipImg)
    print self.view.t.isAlive()
    
  def rateIndicator(self):
    if self.model.loadBool:
      highlight = True
    else: highlight = False
    print highlight
    len = 8
    frame = 0
    while frame < len:
      self.view.displayFrmRate(self.model.flipRate[frame],\
                               float(self.model.dRate), frame, highlight)
      frame = (frame + 1)%8
    #self.rateIndicator()

  def autoLoad(self):
    self.model.loadSavedFolder()
    if self.model.loadBool:
      self.display()
      self.view.t2.loadB = False

  def loadLogo(self):
     self.model.loadLogo()
     self.play()

  def frameRate(self):
    self.model.dRate = self.view.frmRate1.get()
    
  def frameUpdate(self, event):
    self.frameRate()

  def play(self):
   self.Stop = False
   self.len = len(self.model.flipImg)
   while self.frame < self.len and not self.Stop: 
     self.view.display(self.model.flipImg[self.frame], float(self.model.dRate))
     self.view.progBar.step(float(100)/self.len)
     self.frame = self.frame + 1
      
   if self.frame == self.len: 
     self.view.progBar.stop()
     self.frame = 0

   if self.loop == True:
     self.play()    
   
  def loop(self, event):
    if self.loop == False:
      self.loop = True
      icn = ImageTk.PhotoImage(ImageTk.Image.open("icons/loop.gif"))
    else: 
      self.loop = False
      icn = ImageTk.PhotoImage(ImageTk.Image.open("icons/single.gif"))
    event.widget.configure(image=icn)
    event.widget.image=icn
    self.view.root.update_idletasks()

  def stop(self):
    self.Stop = True 

if __name__ == "__main__":
  c = Controller("Test")
  print "model is: ", c.model
  print "view is:  ", c.view
