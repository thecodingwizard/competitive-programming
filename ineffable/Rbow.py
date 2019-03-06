class Rbow:
  AC = '1;32'
  WA = '1;31'
  TLE = '0;31'
  MLE = '0;31'
  RE = '0;33'
  CE = '1;35'
  
  WE = '1;34'
  HANGUP = '1;30'
  OLE = '1;30'

  RED = '1;31'
  GREEN = '1;32'
  BLUE = '1;34'
  YELLOW = '1;33'
  
  @staticmethod
  def c(clr, s):
    return '\x1b[%sm%s\x1b[0m' % (clr, s)
