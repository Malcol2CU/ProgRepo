import Tkinter as tk
import tkMessageBox
import ttk as ttk
import controller
import os
from PIL import ImageTk
import threading
import time

class NotAController(object):
  print "Testing View..."
  
class View(object):
  def __init__(self, controller):
    self.controller = controller
    self.root = tk.Tk()
    self.t = None
    self.t2 = None
    self.root.bind('<Escape>', lambda event: self.saveOnClose())
    self.root.protocol("WM_DELETE_WINDOW", self.saveOnClose)
    self.root.configure(bg = "#EFF5FF", bd=5, relief=tk.FLAT)
    self.root.title('FLIP-PY GIFANIMATOR')
    self.makeMenu()
    self.makeView()

  # Save data on any close option
  def saveOnClose(self):
    self.controller.saveXMLData()
    self.root.destroy()

  def makeMenu(self):
    self.menuPanel = tk.Frame(height=20)
    self.menuPanel.configure(bg="#EFF5FF")

    #File Menu Button Icon
    flIcon = tk.PhotoImage(file="icons/fil.png")
    self.btFile = tk.Menubutton(self.menuPanel, image=flIcon, text="File",\
                               compound=tk.LEFT)
    self.btFile.image = flIcon
    self.btFile.configure(bg="#EFF5FF")
    self.btFile.config(menu=self.btFile)
    fileMenu = tk.Menu(self.btFile, tearoff=0)
    fileMenu.add_command(label="Load", command=self.controller.load)
    fileMenu.add_command(label="Intro", command=self.controller.loadLogo)
    fileMenu.add_command(label="Kill", command=self.root.quit)
    self.btFile.config(menu=fileMenu)
    
    #Editor Selection Menu
    edIcon = tk.PhotoImage(file="icons/immag.png")
    self.btEdit = tk.Menubutton(self.menuPanel, image=edIcon, text="Convert",\
                               compound=tk.LEFT)
    self.btEdit.image = edIcon
    self.btEdit.configure(bg="#EFF5FF")
    self.btEdit.config(menu=self.btEdit)

    editBar = tk.Menu(self.btEdit, tearoff=0)
    editBar.config(bg="#EFF5FF", relief=tk.FLAT)
    sizeMenu = tk.Menu(editBar, tearoff=0)
    sizeMenu.add_command(label="25%", command = lambda: self.controller.percent(25))
    sizeMenu.add_command(label="50%", command = lambda:self.controller.percent(50))
    sizeMenu.add_command(label="75%", command = lambda:self.root.percent(75))
    sizeMenu.add_command(label="125%", command = lambda:self.controller.percent(125))
    sizeMenu.add_command(label="150%", command = lambda:self.controller.percent(150))
    sizeMenu.add_command(label="175%", command = lambda:self.root.percent(175))
    editBar.add_cascade(menu=sizeMenu, label="Re-Size")
    drawMenu = tk.Menu(editBar, tearoff=0)
    drawMenu.add_command(label="Pencil", command = lambda: self.controller.transpose("sketch"))
    drawMenu.add_command(label="Chalk", command = lambda: self.controller.transpose("chalk"))
    drawMenu.add_command(label="Emboss", command = lambda: self.root.transpose("emboss"))
    editBar.add_cascade(menu=drawMenu, label="Re-Sketch")
    self.btEdit.config(menu=editBar)

  def makeView(self):
    #main center view
    screen = tk.PhotoImage(file="icons/Logo/FLIP-Py0.png")
    self.viewer = tk.Label(width=900, height=660, image=screen)
    self.viewer.image = screen
    self.viewer.configure(bg="#000000")

    #thin left edge
    ltPanel = tk.Frame(width=5)
    ltPanel.configure(bg="#EFF5FF")

    #thin right edge
    rtPanel = tk.Frame(width=5)
    rtPanel.configure(bg="#EFF5FF")

    #between viewer and progress bar
    separator = tk.Frame(bg="#EFF5FF", height=5, bd=1, relief=tk.SUNKEN)

    #panel progress bar sits on above bottom panel
    progPanel = tk.Frame(height=10)
    progPanel.configure(bg="#EFF5FF")
    
    #Progress Bar, sits above bottom panel
    self.progBar = ttk.Progressbar(progPanel, orient='horizontal',\
                                   mode='determinate')
    #Bottom Frame, Play, Strop
    bmPanel = tk.Frame(height=35)
    bmPanel.configure(bg="#EFF5FF")
    
    #Play Button
    playIcon = tk.PhotoImage(file="icons/play.png")
    btPlay = tk.Button(bmPanel, image=playIcon)
    btPlay.image = playIcon
    btPlay.configure(bg="#EFF5FF", command=self.thread)

    #Loop Button
    loopIcon = tk.PhotoImage(file="icons/single.gif")
    self.btLoop = tk.Button(bmPanel, image=loopIcon)
    self.btLoop.bind("<Button-1>", self.controller.loop)
    self.btLoop.image = loopIcon
    self.btLoop.configure(bg="#EFF5FF")


    #Stop Button
    stopIcon = tk.PhotoImage(file="icons/stop.png")
    btStop = tk.Button(bmPanel, image=stopIcon)
    btStop.image = stopIcon
    btStop.configure(bg="#EFF5FF", command=self.controller.stop)

    #Step Left Button, Bottom Panel
    ltIcon = tk.PhotoImage(file="icons/rewind.png")
    stepLt = tk.Button(bmPanel, image=ltIcon)
    stepLt.image = ltIcon
    stepLt.configure(bg="#EFF5FF", command=self.controller.stepLt)

    #Step Right Button, Bottom Panel
    rtIcon = tk.PhotoImage(file="icons/fastforward.png")
    stepRt = tk.Button(bmPanel, image=rtIcon)
    stepRt.image = rtIcon
    stepRt.configure(bg="#EFF5FF", command=self.controller.stepRt)


    #Frame Rate Indicator that shows frame rate and autoloads saved Giffy
    rateInd = tk.PhotoImage(file="icons/Loading/ld1.png")
    self.btInd = tk.Button(bmPanel, image=rateInd)
    self.btInd.image = rateInd
    self.btInd.configure(bg="#EFF5FF", command=self.controller.autoLoad)

    #Frame Rate Selector
    rateVar = tk.StringVar(bmPanel)
    rateVar.set(self.controller.model.dRate)
    self.frmRate1 = tk.Spinbox(bmPanel, from_=0, to=9, increment=.005, format="%0.3f", wrap=True)
    self.frmRate1.bind("<Return>", self.controller.frameUpdate)
    self.frmRate1.bind("<KP_Enter>", self.controller.frameUpdate)
    self.frmRate1.configure(bg="#EFF5FF", width=5, textvariable=rateVar,\
                            command=self.controller.frameRate)
    
    #Frame Rate Labels
    lblRate = tk.Label(bmPanel, text="Refresh-Rate")
    lblRate.configure(bg="#EFF5FF")
    lblSec = tk.Label(bmPanel, text="s")
    lblSec.configure(bg="#EFF5FF")

    #Panel Packing Order Matters
    self.menuPanel.pack(side=tk.TOP, fill=tk.X)
    self.btFile.pack(side=tk.LEFT)
    self.btEdit.pack(side=tk.LEFT)
    ltPanel.pack(side=tk.LEFT, fill=tk.Y)
    rtPanel.pack(side=tk.RIGHT, fill=tk.Y)
    self.viewer.pack(side=tk.TOP,expand=True, fill=tk.BOTH)
    self.progBar.pack(expand=True, side=tk.TOP, fill=tk.BOTH)
    btPlay.pack(side=tk.LEFT)
    self.btLoop.pack(side=tk.LEFT)
    btStop.pack(side=tk.LEFT)
    stepLt.pack(side=tk.LEFT)
    stepRt.pack(side=tk.LEFT)
    lblSec.pack(side=tk.RIGHT)
    self.btEdit.pack(side=tk.LEFT)
    self.frmRate1.pack(side=tk.RIGHT)
    self.btInd.pack(side=tk.RIGHT)
    lblRate.pack(side=tk.RIGHT)
    bmPanel.pack(side=tk.BOTTOM, fill=tk.X)
    progPanel.pack(side=tk.BOTTOM, fill=tk.X)
    separator.pack(side=tk.BOTTOM, fill=tk.X)
 
  def thread(self):
    if self.t == None or not self.t.isAlive(): 
      self.t = threading.Thread(target=self.controller.play)
      self.t.daemon = True
      self.t.start()

  def thread2(self):
    if self.t2 == None or not self.t2.isAlive():
      self.controller.model.loadSettings()
      self.t2 = threading.Thread(target=self.controller.rateIndicator)
      self.t2.loadB = True
      self.t2.bG = ["#EFF5FF","#D6F5FF","#C1F5FF","#C1E0FF",\
                    "#C1E0FF","#C1F5FF","#D6F5FF","#EFF5FF"]
      self.t2.daemon = True
      self.t2.start()

  def display(self, img, fR):
    newimg = ImageTk.PhotoImage(ImageTk.Image.open(img))
    self.viewer.configure(image=newimg)
    self.viewer.image=newimg
    self.root.update_idletasks()
    time.sleep(float(fR))
   
  def displayFrmRate(self, img, fR, frame, hl):
    if hl and self.t2.loadB:
      self.btInd.configure(bg=str(self.t2.bG[frame]))
      self.btInd.bg=str(self.t2.bG[frame])
    else:
      self.btInd.configure(bg="#EFF5FF")
      self.btInd.bg="#EFF5FF"
    newimg = ImageTk.PhotoImage(ImageTk.Image.open(img))
    self.btInd.configure(image=newimg)
    self.btInd.image=newimg

    self.root.update_idletasks()
    time.sleep(fR)
    
if __name__ == "__main__":
  view = View(NotAController())
  tk.mainloop()
