# -*- coding: utf-8 -*-
#example start:
#function API
from __future__ import with_statement
import sys
import sys, stat, os
import locale
import os.path, time
import shutil
from subprocess import call
from win32api import GetFileVersionInfo, LOWORD, HIWORD


PATCH = "C:\\install\\darun-grim-script-read-only\\test3\\9.0.597.107"
ID_PATCH = "9.0.597.107"
UNPATCH = "C:\\install\\darun-grim-script-read-only\\test3\\9.0.597.98"
ID_UNPATCH = "9.0.597.98"
List = []
DarunGrim3_PATH = "C:\\install\\darun-grim-script-read-only\\"
PYTHON_26 = "C:\\Python26\\python.exe"


def get_version_number (filename):
  #print filename
  info = GetFileVersionInfo (filename, "\\")
  ms = info['FileVersionMS']
  ls = info['FileVersionLS']
  return HIWORD (ms), LOWORD (ms), HIWORD (ls), LOWORD (ls)

def recursive_ls(i,file_path,id_file_path):
    flag = 0
    files=os.listdir(file_path+"\\"+i+"\\")
    files=[filename for filename in files if filename[0] != '.']
    #print files
    
    for j in files:
	if os.path.isdir(file_path+"\\"+i+"\\"+j):
	    #print 'dir=%s'%i
	    recursive_ls(i+"\\"+j,file_path,id_file_path)
	else:
	    #print UNPATCH+"\\"+i+"\\"+j
	    t_dll = j.find("dll") 
	    t_exe = j.find("exe") 
	    if t_dll != -1 or t_exe != -1:
	        #print file_path+"\\"+i+"\\"+j
	        tmp = []
		all_path = file_path+"\\"+i+"\\"+id_file_path+"."+j
		tmp.append(j)
		tmp.append(all_path)
		List.append(tmp)
	        shutil.move(file_path+"\\"+i+"\\"+j,file_path+"\\"+i+"\\"+id_file_path+"."+j)
#    print List
#    return List

def list_file(file_path,id_file_path):
    #List_R = []
    files=os.listdir(file_path)
	#ignore files starting with '.' using list comprehension
    files=[filename for filename in files if filename[0] != '.']
    
    #print files
    #for j in files:
#	print UNPATCH+"\\"+j
    
    for i in files:
	if os.path.isdir(file_path+"\\"+i):
	    #print 'dir=%s'%i
	    recursive_ls(i,file_path,id_file_path)
	else:
	    t_dll = i.find("dll") 
	    t_exe = i.find("exe") 
	    if t_dll != -1 or t_exe != -1:
		#print file_path+"\\"+i
		tmp = []
		all_path = file_path+"\\"+id_file_path+"."+i
		tmp.append(i)
		tmp.append(all_path)
		List.append(tmp)
		shutil.move(file_path+"\\"+i, file_path+"\\"+id_file_path+"."+i)
		
		#File = UNPATCH+"\\"+i
		#print ".".join ([str (i) for i in get_version_number (File)])
    #for r in List_R:
	#print r
	#List.append(r)
    #return List

if __name__ == "__main__":
    List_unpatch = []
    List_patch = []
    #filename = os.environ["COMSPEC"]
    #filename = "C:\\install\\darun-grim-script-read-only\\test1\\win32k.5.1.2600.6064.sys"
    #print filename
    #print ".".join ([str (i) for i in get_version_number (filename)])
    #print "unpatch"
    list_file(UNPATCH,ID_UNPATCH)
    for k in  List:
	#print k
	List_unpatch.append(k)
    del List[:]
    #print "patch"
    list_file(PATCH,ID_PATCH)
    for j in List:
	#print j
	List_patch.append(j)
    
    '''print "unpatch"	
    for t in List_unpatch:
	  print t
    print "patch"
    for tt in List_patch:
	  print tt'''
    
    for i in List_unpatch:
	for l in List_patch:
	    if i[0] == l[0]:
		#print i[0]
		command = PYTHON_26+" "+DarunGrim3_PATH+"dgScript.py -c "+DarunGrim3_PATH+"DarunGrim3.cfg -o "+i[1]+" -p "+l[1]+" -v  > "+ UNPATCH +"\\"+i[0]+".debug.txt"
		print command
		call(command)
    
    
    
    