from cs50 import get_float

change_owed = -1.0
coins_needed = 0

while change_owed < 0:
    change_owed = get_float("Change owed: ")

n_quarters = change_owed // 0.25
change_owed -= n_quarters * 0.25

n_dimes = change_owed // 0.1
change_owed -= n_dimes * 0.1

n_nickels = change_owed // 0.05
change_owed -= n_nickels * 0.05

n_pennies = change_owed // 0.01
change_owed -= n_pennies * 0.01

print(f"{change_owed}")

if change_owed:
    raise ValueError(f"The fuck... {change_owed = }")

print(f"{int(n_quarters + n_dimes + n_nickels + n_pennies)}")
