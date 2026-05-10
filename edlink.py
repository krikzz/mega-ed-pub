
import os
import sys
import platform
import subprocess
import shutil

USBTOOL = "edlink.exe"

def main():
    script_dir = os.path.dirname(os.path.abspath(__file__))
    app_path = os.path.join(script_dir, USBTOOL)

    if not os.path.isfile(app_path):
        print("error: edlink.exe not found: " + app_path, file=sys.stderr)
        sys.exit(1)

    args = sys.argv[1:]

    if platform.system() == "Windows":
        cmd = [app_path] + args
    else:
        if shutil.which("mono") is None:
            print("error: mono runtime is not installed", file=sys.stderr)
            sys.exit(1)

        cmd = ["mono", app_path] + args

    result = subprocess.run(cmd)
    sys.exit(result.returncode)

if __name__ == "__main__":
    main()
