import commands as cmd

#with open("SSWW_2016_HNMultiLep.txt") as f:
with open("Control_2016_HNMultiLep.txt") as f:
  lines = f.readlines()

#with open("SSWW_2016_NoSkim.txt") as f:
#  lines2 = f.readlines()

print "!!!!!!!!!!2016a!!!!!!!!!!"
for line in lines:
  if '#' in line:
    line = line[1:-1]
  line = line.strip()
  print cmd.getoutput("ls /data6/Users/jihkim/SKFlatAnalyzer/data/Run2UltraLegacy_v2/2016preVFP/Sample/ForSNU | grep "+line)

print "!!!!!!!!!!2016b!!!!!!!!!"
for line in lines:
  if '#' in line:
    line = line[1:-1]
  line = line.strip()
  print cmd.getoutput("ls /data6/Users/jihkim/SKFlatAnalyzer/data/Run2UltraLegacy_v2/2016postVFP/Sample/ForSNU | grep "+line)

#print "NoSkim;"
#print "2016a"
#for line in lines2:
#  if '#' in line:
#    line = line[1:-1]
#  line = line.strip()
#  print cmd.getoutput("ls /data6/Users/jihkim/SKFlatAnalyzer/data/Run2UltraLegacy_v2/2016preVFP/Sample/ForSNU | grep "+line)
#
#print "2016b"
#for line in lines2:
#  if '#' in line:
#    line = line[1:-1]
#  line = line.strip()
#  print cmd.getoutput("ls /data6/Users/jihkim/SKFlatAnalyzer/data/Run2UltraLegacy_v2/2016postVFP/Sample/ForSNU | grep "+line)