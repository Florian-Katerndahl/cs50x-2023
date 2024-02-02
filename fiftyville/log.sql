-- Keep a log of any SQL queries you execute as you solve the mystery.

-- get id from crime reports that mentions theft of CS50 duck: 295
-- duck was stolen at 10:15am
SELECT id, description FROM crime_scene_reports
WHERE year = 2021 AND month = 7 AND day = 28 AND street = "Humphrey Street" AND description LIKE "%duck%";

-- get transcript of interviews with witnesses
-- Ruth: thief drove away within 10 minutes
-- Eugene: thief withdrew money at Leggett Street in the morning
-- Raymond: talked on the phone, planning to take earliest flight out of fiftyville on next day; ticket purchased by someone else
SELECT name, transcript FROM interviews
WHERE year = 2021 AND month = 7 AND day = 28 AND transcript LIKE "%bakery%";

-- WHY THE FUCK IS THIS airports.city and what the heck is airport_full_name then?
-- ok, the full_name is the full airport name. Still confusing :/
SELECT people.name, people.phone_number, airports.city FROM atm_transactions
JOIN bank_accounts ON atm_transactions.account_number = bank_accounts.account_number
JOIN people ON bank_accounts.person_id = people.id
JOIN passengers ON people.passport_number = passengers.passport_number
JOIN flights ON passengers.flight_id = flights.id
JOIN airports ON flights.destination_airport_id = airports.id
JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
JOIN phone_calls ON people.phone_number = phone_calls.caller
WHERE
    -- select all people who withdrew cash at ATM Legget Street not 28th july 2021
    (atm_transactions.year = 2021 AND atm_transactions.month = 7 AND atm_transactions.day = 28 AND atm_transactions.atm_location = "Leggett Street" AND atm_transactions.transaction_type = "withdraw")
    -- select all pepople who additionally left the bakery by car on the 28th july 2021 between 10:5 and 10:25
    AND (bakery_security_logs.year = 2021 AND bakery_security_logs.month = 7 AND bakery_security_logs.day = 28 AND bakery_security_logs.hour = 10 AND bakery_security_logs.minute >= 15 AND bakery_security_logs.minute <= 25 AND bakery_security_logs.activity = "exit")
    -- select all people who additionally took a flight on the 29th july 2021
    AND (flights.year = 2021 AND flights.month = 7 AND flights.day = 29)
    -- select all people who additionally called someone on 28th july 2021 for less than a minute
    AND (phone_calls.year = 2021 AND phone_calls.month = 7 AND phone_calls.day = 28 AND phone_calls.duration <= 60)
-- thief took earliest flight and does not get accompanied (which I thought the interviewee meant with they)
ORDER BY flights.hour, flights.minute
LIMIT 1;

-- who did the thief (Bruce) call?
SELECT name AS accomplice FROM people
JOIN phone_calls ON people.phone_number = phone_calls.receiver
WHERE caller = "(367) 555-5533" AND day = 28 AND month = 7 AND year = 2021 AND duration <= 60;
