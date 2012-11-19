############################
#
# IMPORTS
#
############################
import sys, os, subprocess, getopt
############################
#
# GLOBALS
#
############################
html = 0
javascript = 0
css = 0
############################
#
# SUBROUTINES
#
############################
def upload(file):
	if os.path.isdir(file) == True:
		upload(file) #recursively browse directory tree downward
	else:
		if (not(file.endswith('.py'))): #upload everything but this script!
			if (((file.endswith('.htm')) and (html == 1)) or ((file.endswith('.js')) and (javascript == 1)) or ((file.endswith('.css')) and (css == 1))):
				print "uploading " + file
				subprocess.call("curl -v -0 -T " + file + " http://192.168.1.9/upload/")

				
############################
#
# MAIN PROGRAM
#
############################
try:
    opts, args = getopt.getopt(sys.argv[1:],"hjc",["html","javascript", "css"]) 
except getopt.GetoptError:
		print 'test.py -i <inputfile> -o <outputfile>'
		sys.exit(2)
if (not(opts)):
	print "including all file types"
	html = 1
	javascript = 1
	css = 1
for opt, arg in opts:
	if opt in ("-h", "--html"):
		html = 1
	elif opt in ("-j", "--javascript"):
		javascript = 1
	elif opt in ("-c", "--css"):
		css = 1

files = os.listdir('.')

for file in files:	
	upload(file)
	