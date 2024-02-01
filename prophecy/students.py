from cs50 import SQL
import csv

db = SQL("sqlite:///roster.db")

rows = []
houses = set()
heads = set()
with open("students.csv", "rt") as f:
    reader = csv.DictReader(f)
    for row in reader:
        rows.append(row)

for row in rows:
    db.execute("INSERT INTO students (name)"
               "VALUES (?)", row["student_name"])
    houses |= set((row["house"], row["head"]))

print(houses)

for house in houses:
    db.execute("INSERT INTO houses (name, head)"
               "VALUES (?, ?)", house[0], house[1])

