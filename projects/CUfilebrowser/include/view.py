import Tkinter as tk
import tkMessageBox
import controller
import os

class NotAController(object):
  def openFile(self): print "open file"
  def getFiles(self): print "get files"
  def getDirs(self): print "get dirs"
  def find(self): print "find"

class View(object):
  def __init__(self, controller):
    self.controller = controller
    root = tk.Tk()
    root.bind('<Escape>', (lambda event: quit()))
    root.configure(bg = "#193659", padx = 5, pady = 5, bd = 5, relief=tk.SUNKEN)
    root.title('File Manager')

    top = tk.Frame(width = 80, height=300)
    top.configure(bg = "#506B8C", padx = 5, pady = 5)
    tb = tk.Frame(height=500, width = 90)
    tb.configure(bg = "#506B8C", padx = 5, pady =2)
    bottom = tk.Frame(height=100, width = 80, bd = 5, relief=tk.SUNKEN,\
                      bg="#FFE1B1")
    bottomtop = tk.Frame(bottom, relief=tk.FLAT,bg="#FFE1B1",width=80)
    separator = tk.Frame(height=2, bd=1, relief=tk.SUNKEN)
    
    scrollbary = tk.Scrollbar(bottom, orient=tk.VERTICAL)
    scrollbarx = tk.Scrollbar(bottom, orient=tk.HORIZONTAL)
    self.listbox = tk.Listbox(bottom,yscrollcommand=scrollbary.set, xscrollcommand=scrollbarx.set)
    
    scrollbary.config(command=self.listbox.yview, bg="#506B8C")
    scrollbary.pack(side=tk.RIGHT, fill=tk.Y)
    scrollbarx.config(command=self.listbox.xview, bg="#506B8C")
    scrollbarx.pack(side=tk.BOTTOM, fill=tk.X)
    
    
    self.ld = tk.StringVar()
    listdirectory = tk.Entry(bottomtop, textvariable=self.ld)
    listdirectory.configure(disabledbackground="#FFE1B1", relief=tk.FLAT, font=(10),\
                            disabledforeground="#506B8C", state = "disabled")
    listdirectory.pack(side=tk.LEFT,fill=tk.BOTH,expand="true")
    self.ld.set("File/Folder Information")

    photodel = tk.PhotoImage(file="icons/delete.gif")
    listdirremove = tk.Button(tb,image=photodel, text="Delete",compound="left")
    listdirremove.image = photodel
    listdirremove.configure(bg="#FFE1B1", command=self.controller.deleteFile)
    
    photodoc = tk.PhotoImage(file="icons/doc.gif")
    listdircreate = tk.Button(tb,image=photodoc, text="Create",compound="left")
    listdircreate.image = photodoc
    listdircreate.configure(bg="#FFE1B1", command=self.controller.newFile)

    photogo = tk.PhotoImage(file="icons/change_mode.gif")
    listdirgo = tk.Button(tb,image=photogo, text="Go",compound="left")
    listdirgo.image = photogo
    listdirgo.configure(bg="#FFE1B1", command=self.controller.goDir)
    
    photoclean = tk.PhotoImage(file="icons/remove.gif")
    listdirclean = tk.Button(tb,image=photoclean, text="Clean",\
                             compound="left")
    listdirclean.image = photoclean
    listdirclean.configure(bg="#D89A75", command=self.controller.cleanJunk)

    bottomtop.pack(side=tk.TOP,fill=tk.BOTH)
    
    photopic = tk.PhotoImage(file="icons/paw.gif")
    self.listbox.bind("<Double-Button-1>", self.controller.openFile)
    self.listbox.bind("<Delete>", self.controller.deleteFile)
    self.listbox.bind('<<ListboxSelect>>', self.controller.displayP)
    self.listbox.configure(height=20,bg = "#FFE1B1", font=(10), relief=tk.FLAT, selectmode=tk.EXTENDED)
    self.listbox.pack(side = "left" ,fill=tk.BOTH, expand="true")
    
    label = tk.Label(bottom, image = photopic)
    label.image = photopic
    label.configure(bg="#FFE1B1")
    label.pack(side="right", fill=tk.BOTH, expand ="true")
    
    photo=tk.PhotoImage(file="icons/paw2.gif")
    button = tk.Button(top, image = photo)
    button.image = photo
    button.configure(bg="#FFE1B1")
    button.pack(side="left", padx = 5, pady = 5)
    button.configure(command=self.controller.back)
    
    self.dir = tk.StringVar()
    directory = tk.Entry(top, textvariable=self.dir)
    directory.bind("<Return>", self.controller.changeDir)
    directory.configure(bg="#FFE1B1",bd=5, relief=tk.SUNKEN, width=80,\
                        font=(10))
    directory.pack(side = "left")
    self.dir.set(os.getcwd())
    
    labelsearch = tk.Label(tb)
    labelsearch.configure(bg="#506B8C",fg="#FFE1B1", text="Search")
    labelsearch.pack(side=tk.LEFT)

    self.s = tk.StringVar()
    self.s.trace('w', self.my_tracer)
    search = tk.Entry(tb, textvariable=self.s)
    search.configure(bg="#FFE1B1",bd = 5, relief=tk.SUNKEN,font=(10))
    search.pack(side = "left")
    
    listdirgo.pack(side=tk.LEFT)
    listdircreate.pack(side=tk.LEFT)
    listdirremove.pack(side=tk.LEFT)
    listdirclean.pack(side=tk.LEFT)
    search.focus()

    top.pack(side = "top", expand = False, fill=tk.BOTH, ipadx = 30, ipady = 5)
    tb.pack(side = "top", expand = False, fill=tk.BOTH)
    separator.pack(fill=tk.X, padx=5, pady=5)
    bottom.pack(side = "bottom", expand = True, fill=tk.BOTH)

  def my_tracer(self,a, b, c): 
    if self.s.get() != "Search":
      self.controller.find(self.s.get())
      
  def notify(self):
    self.ld.set("File/Folder Information")
    self.listbox.config(state = tk.NORMAL)
    self.dir.set(os.getcwd())
    self.listbox.delete(0, tk.END)
    
    for item in self.controller.getFiles():
      self.listbox.insert(tk.END, os.path.basename(item))
    
    for item in self.controller.getDirs():
        self.listbox.insert(tk.END, os.path.basename(item))
    
    for x in range(self.listbox.size()):
      for dir in self.controller.getDirs():
        if self.listbox.get(x) == os.path.basename(dir):
          self.listbox.itemconfig(x, fg="#E66B00")
    
  def search(self):
    self.ld.set("File/Folder Information")
    self.listbox.config(state = tk.NORMAL)
    self.listbox.delete(0, tk.END)
    for item in self.controller.getFiles():
      self.listbox.insert(tk.END, item)
    
    for item in self.controller.getDirs():
        self.listbox.insert(tk.END, item)
    
    for x in range(self.listbox.size()):
      for dir in self.controller.getDirs():
        if self.listbox.get(x) == dir:
          self.listbox.itemconfig(x, fg="#E66B00")
    if self.listbox.size() == 0 and self.s.get() != "": 
      self.listbox.insert(tk.END, "No Result!!")
      self.listbox.config(state = tk.DISABLED)
      
if __name__ == "__main__":
  view = View(NotAController())
  tk.mainloop()
