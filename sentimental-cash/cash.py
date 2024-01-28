from cs50 import get_float

change_owed = -1.0

while change_owed < 0:
    change_owed = get_float("Change owed: ")

change_owed = int(change_owed * 100)

n_quarters = change_owed // 25
change_owed -= n_quarters * 25

n_dimes = change_owed // 10
change_owed -= n_dimes * 10

n_nickels = change_owed // 5
change_owed -= n_nickels * 5

n_pennies = change_owed // 1
change_owed -= n_pennies * 1

if change_owed:
    raise ValueError(f"The fuck... {change_owed = }")

print(f"{int(n_quarters + n_dimes + n_nickels + n_pennies)}")
