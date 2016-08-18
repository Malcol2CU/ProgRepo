class Stack(object):
  def __init__(self):
    self.stk = []
  def push(self, x):
    self.stk.append(x)
  def top(self):
    return self.stk[-1]
  def pop(self):
    del self.stk[-1]
  def empty(self):
    return len(self.stk) == 0


if __name__ == "__main__":
  n = raw_input("Type a decimal number: ")
  n = int(n)

  stk = Stack()
  while n:
    stk.push( n % 2 )
    n = n/2
  
  while not stk.empty():
    print stk.top(),
    stk.pop()
  print
  

