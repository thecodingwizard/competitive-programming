import sys, os, json
from Rbow import *

class IneffableHelper:
  def __init__(self, configfile):
    self.configfile = configfile
    self.configdir = os.path.dirname(self.configfile)

    self._harvest_config()
    self._cook_config()

  def _harvest_config(self):
    readconfig = open(self.configfile)
    lines = readconfig.readlines()
    readconfig.close()
    
    jsonstr = ''
    for line in lines:
      jsonstr += line
    
    self.rawconfig = json.loads(jsonstr)

  def _cook_config(self):
    if 'execute' not in self.rawconfig:
      print Rbow.c(Rbow.RED, '\nArrgh!!! No \'execute\' parameter found in config file\n')
      sys.exit()
    else:
      self.execute = self.rawconfig['execute']

    self.pkdesc = self.rawconfig['pkdesc'] if 'pkdesc' in self.rawconfig else None
    self.pbcode = self.rawconfig['pbcode'] if 'pbcode' in self.rawconfig else None
    self.tl = self.rawconfig['tl'] if 'tl' in self.rawconfig else None
    self.ml = self.rawconfig['ml'] if 'ml' in self.rawconfig else None
    self.warmup = self.rawconfig['warmup'] if 'warmup' in self.rawconfig else None
    self.tstdir = self.rawconfig['tstdir'] if 'tstdir' in self.rawconfig else '.'

    if self.tl is not None and not isinstance(self.tl, int):
      print Rbow.c(Rbow.RED, '\nArrgh!!! \'tl\' is not an integer\n')
      sys.exit()
    if self.ml is not None and not isinstance(self.ml, int):
      print Rbow.c(Rbow.RED, '\nArrgh!!! \'ml\' is not an integer\n')
      sys.exit()

    if self.pbcode is not None:
      self.execute = self.execute.replace('{PROBLEM}', self.pbcode)
      if self.warmup is not None:
        self.warmup = self.warmup.replace('{PROBLEM}', self.pbcode)
      if self.tstdir is not None:
        self.tstdir = self.tstdir.replace('{PROBLEM}', self.pbcode)

    if 'iopairs' not in self.rawconfig and ('inp' not in self.rawconfig or 'out' not in self.rawconfig):
      print Rbow.c(Rbow.RED, '\nArrgh!!! No \'iopairs\' or (\'inp\', \'out\') parameter(s) found in config file\n')
      sys.exit()
    else:
      self.inp = None
      self.out = None
      self.iopairs = None

      if 'inp' in self.rawconfig and 'out' in self.rawconfig:
        self.inp = self.rawconfig['inp']
        self.out = self.rawconfig['out']
        if self.pbcode is not None:
          self.inp = self.inp.replace('{PROBLEM}', self.pbcode)
          self.out = self.out.replace('{PROBLEM}', self.pbcode)

	if self.inp.find('**') != -1 or self.out.find('**') != -1:
          print Rbow.c(Rbow.RED, '\nArrgh!!! \'inp\' and/or \'out\' should not contain two consecutive \'*\' wildchars\n')
          sys.exit()
	if self.inp.count('*') > self.out.count('*'):
          print Rbow.c(Rbow.RED, '\nArrgh!!! Number of \'*\' wildchars of \'out\' is less than that of \'inp\'\n')
          sys.exit()

	self.iopairs = {}
	self._init_iopairs()
      else:
        self.iopairs = self.rawconfig['iopairs']
    

    if len(self.iopairs) == 2 and 'inp' in self.iopairs and 'out' in self.iopairs:
      if len(self.iopairs['inp']) != len(self.iopairs['out']):
        print Rbow.c(Rbow.RED, '\nHeyyy!!! Number of input and output files specified in config file do not match\n')
      foo = {}
      ntests = min(len(self.iopairs['inp']), len(self.iopairs['out']))
      for i in xrange(ntests):
        foo[ self.iopairs['inp'][i] ] = self.iopairs['out'][i]
      self.iopairs = foo.copy()

  def inp_matches(self, filename):
    if self.inp == '*':
      return (True, [filename])

    lst = 0
    kwds = self.inp.split('*')
    prms = []
    
    if self.inp[0] == '*':
      lst = 0
    else:
      if filename[:len(kwds[0])] != kwds[0]:
        return (False, [1])
      else:
        lst = len(kwds[0])

    if self.inp[-1] == '*':
      kwds = kwds[:-1]

    for i in xrange(1, len(kwds)):
      idx = filename.find(kwds[i], lst+1)

      if idx == -1:
        return (False, [3])
      else:
        prms.append(filename[lst:idx])

      lst = idx + len(kwds[i])
    
    if self.inp[-1] == '*':
      if lst < len(filename):
        prms.append(filename[lst:])
      else:
        return (False, [5])
    elif lst != len(filename):
      return (False, [4])

    return (True, prms)

  def out_equivalent(self, params):
    kwds = self.out.split('*')
    ret = kwds[0]

    for i in xrange(1, len(kwds)):
      ret += params[i-1] + kwds[i]
    
    return ret

  def _init_iopairs(self):
    files = os.listdir( os.path.join(self.configdir, self.tstdir) )
    self.iopairs = {}

    for inp in files:
      if os.path.isfile( os.path.join(self.configdir, self.tstdir, inp) ):
        (matches, params) = self.inp_matches(inp)
        if matches:
          out = self.out_equivalent(params)
          if os.path.isfile( os.path.join(self.configdir, self.tstdir, out) ):
            self.iopairs[inp] = out
