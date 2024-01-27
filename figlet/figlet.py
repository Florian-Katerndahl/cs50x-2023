import sys
import pyfiglet

if sys.argc != 1 or sys.argc != 3:
    print("ERROR: Invalid usage")
    print("figlet.py [-f|--font fontname]")
    sys.exit(1)

if sys.argc == 3:
    
