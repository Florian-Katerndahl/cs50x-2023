-- Keep a log of any SQL queries you execute as you solve the mystery.

-- get id from crime reports that mentions theft of CS50 duck: 295
SELECT id, description FROM crime_scene_reports
WHERE year = 2021 AND month = 7 AND day = 28 AND street = "Humphrey Street" AND description LIKE "%duck%";

-- get transcript of interviews with witnesses
-- Ruth: thief drove away within 10 minutes
-- Eugene: thief withdrew money at Legnett Street in the morning
-- Raymond: planning to take earliest flight out of fiftyville; ticket purchased by someone else
SELECT name, transcript FROM interviews
WHERE year = 2021 AND month = 7 AND day = 28 AND transcript LIKE "%bakery%";

