import os
import sys
import subprocess
import shutil

USBTOOL = "../edlink.py"

FPG_SRC = "../fpga/fpga_core/map_ssf/output_files/mega-core"

ARGS = ["run", "--file", "ssf-tst.md", "--fpga", FPG_SRC+".x25"]


def main():
    if not os.path.isfile(USBTOOL):
        print("error: edlink.py not found: " + USBTOOL, file=sys.stderr)
        sys.exit(1)

    shutil.copy(FPG_SRC+".rbf", FPG_SRC+".x25")
    
    cmd = [sys.executable, USBTOOL] + ARGS

    result = subprocess.run(cmd)
    sys.exit(result.returncode)

if __name__ == "__main__":
    main()
