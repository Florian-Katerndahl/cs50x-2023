import sys
from pyfiglet import Figlet

if sys.argc != 1 or sys.argc != 3:
    print("Invalid usage")
    sys.exit(1)

f = Figlet()

if sys.argc == 3:
    if sys.argv[1] not in ["-f", "--force"]:
        print("Invalid usage")
        sys.exit(1)
    f = Figlet(font=sys.argv[2])

user_input = input("Input: ")

print("Output")

print(f.renderText())
