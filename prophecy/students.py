from cs50 import SQL
import csv

db = SQL("sqlite:///roster.db")

rows = []
houses = set()
with open("students.csv", "rt") as f:
    reader = csv.DictReader(f)
    for row in reader:
        rows.append(row)

for row in rows:
    db.execute("INSERT INTO students (name)"
               "VALUES (?)", row["student_name"])
    houses.add((row["house"], row["head"]))

for house in houses:
    db.execute("INSERT INTO houses (name, head)"
               "VALUES (?, ?)", house[0], house[1])

for row in rows:
    sid = db.execute("SELECT id FROM students WHERE name = ?", row["student_name"])
    hid = db.execute("SELECT id FROM houses WHERE name = ?", row["house"])
    db.execute("INSERT INTO house_assignments (student_id, house_id)"
               "VALUES (?, ?)", sid[0]["id"], hid[0]["id"])
