import sys
from pyfiglet import Figlet

if len(sys.argv) != 1 or len(sys.argv) != 3:
    print("Invalid usage")
    print(sys.argv)
    sys.exit(1)

f = Figlet()

if len(sys.argv) == 3:
    if sys.argv[1] not in ["-f", "--force"]:
        print("Invalid usage")
        sys.exit(1)
    f = Figlet(font=sys.argv[2])

user_input = input("Input: ")

print("Output")

print(f.renderText())
