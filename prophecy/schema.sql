CREATE TABLE IF NOT EXISTS students (
    id INTEGER,
    name TEXT,
    PRIMARY KEY(id)
);

CREATE TABLE IF NOT EXISTS houses (
    id INTEGER,
    name TEXT,
    head TEXT,
    PRIMARY KEY(id)
);

CREATE TABLE IF NOT EXISTS house_assignments (
    student_id INTEGER,
    house_id INTEGER,
    FOREIGN KEY(student_id) REFERENCES students(id),
    FOREIGN KEY(house_id) REFERENCES houses(id)
);

-- Why do you think it’s considered better design not to repeat information like houses and heads for each student?
--  1) It saves some space in memory/on disk
--  2) Information only has to be updated in 1 place
--  3) Information is only found in one place and thus canonical?!
