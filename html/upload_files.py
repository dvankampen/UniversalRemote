import os, subprocess

files = filter(os.path.isfile, os.listdir('.')) 

for file in files:	
	if (file.endswith('.HTM')):
		print "uploading " + file
		subprocess.call("curl -v -0 -T " + file + " http://192.168.1.9/upload/")