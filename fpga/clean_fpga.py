
import os
import shutil
import glob
import pathlib
import msvcrt

def del_dir(path):
	print("del dir: "+path);
	shutil.rmtree(path)
	
def cln_odir(path):
	
	cleaned = False
	flist = os.listdir(path)

	for i in range(len(flist)):

		full_path = path +"\\"+flist[i];
		ext = pathlib.Path(full_path).suffix

		if(ext == ".rbf"):
			continue

		os.remove(full_path)
		cleaned = True;

	if(cleaned):
		print("cln dir: "+path);


def rem_bak(path):
	print("rem bak: "+path);
	os.remove(path)


def clean_dir(path):
	
	#print("scan dir: "+path);

	flist = os.listdir(path)

	
	for i in range(len(flist)):
		
		full_path = path +"\\"+flist[i];

		
		if(pathlib.Path(full_path).suffix == ".bak"):
			rem_bak(full_path)
			continue

		if(os.path.isdir(full_path) == False):
			continue
		
		if(flist[i] == "incremental_db"):
			del_dir(full_path)
			continue
		if(flist[i] == "db"):
			del_dir(full_path)
			continue
		if(flist[i] == "output_files"):
			cln_odir(full_path)
			continue

		clean_dir(full_path)

def clean_fpga():
	
	clean_dir(os.path.abspath(os.getcwd()))

try:
	clean_fpga()
	print("OK");


except Exception as x:
	 print("unexpected error: " + type(x).__name__)

msvcrt.getch()