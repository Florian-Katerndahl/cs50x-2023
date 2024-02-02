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

SELECT license_plate FROM bakery_security_logs
WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 5 AND minute <= 25 AND activity = "exit";

SELECT * FROM people
WHERE license_plate IN (
    SELECT license_plate FROM bakery_security_logs
    WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 5 AND minute <= 25 AND activity = "exit"
);

-- filter flights taking of one day after theft with at least two pepole boarded from person table where one's license plate was recorderd
-- flight ID 36 has thief and comapgnion
-- flight goes to LaGuardia
SELECT flights.id, airports.full_name FROM flights
JOIN passengers ON flights.id = passengers.flight_id
JOIN people ON passengers.passport_number = people.passport_number
JOIN airports ON flights.destination_airport_id = airports.id
WHERE passengers.passport_number IN (
    SELECT passport_number FROM people
    WHERE license_plate IN (
        SELECT license_plate FROM bakery_security_logs
        WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 5 AND minute <= 25 AND activity = "exit"
    )
) AND flights.year = 2021 AND flights.month = 7 AND flights.day = 29
GROUP BY flights.id
HAVING COUNT(*) >= 2;

-- this query returns three people. Two of which were on the same plane. Either one of those (Bruce, Luca) has to be the thief.
SELECT people.id, people.name, people.phone_number, flights.id FROM atm_transactions
JOIN bank_accounts ON atm_transactions.account_number = bank_accounts.account_number
JOIN people ON bank_accounts.person_id = people.id
JOIN passengers ON people.passport_number = passengers.passport_number
JOIN flights ON passengers.flight_id = flights.id
JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
JOIN phone_calls ON people.phone_number = phone_calls.caller
WHERE
    -- select all people who withdrew cash at ATM Legget Street not 28th july 2021
    (atm_transactions.year = 2021 AND atm_transactions.month = 7 AND atm_transactions.day = 28 AND atm_transactions.atm_location = "Leggett Street" AND atm_transactions.transaction_type = "withdraw")
    -- select all pepople who additionally left the bakery by car on the 28th july 2021 between 10:5 and 10:25
    AND (bakery_security_logs.year = 2021 AND bakery_security_logs.month = 7 AND bakery_security_logs.day = 28 AND bakery_security_logs.hour = 10 AND bakery_security_logs.minute >= 5 AND bakery_security_logs.minute <= 25 AND bakery_security_logs.activity = "exit")
    -- select all people who additionally took a flight on the 29th july 2021
    AND (flights.year = 2021 AND flights.month = 7 AND flights.day = 29)
    -- select all people who additionally called someone on 28th july 2021 for less than a minute
    AND (phone_calls.year = 2021 AND phone_calls.month = 7 AND phone_calls.day = 28 AND phone_calls.duration <= 60);

-- suspected thief or helper talked on phone with whom?
-- Luca was called by Walter and Kathryn, only ... was also on flight ID 36 to LaGuardia Airport
SELECT id, caller, receiver, year, month, day, duration, pcaller, preceiver FROM phone_calls
JOIN (SELECT phone_number as caller_num, name as pcaller FROM people) ON caller_num = phone_calls.caller
JOIN (SELECT phone_number as reciever_num, name as preceiver FROM people) ON reciever_num = phone_calls.receiver
WHERE year = 2021 AND month = 7 AND day = 28 AND phone_calls.duration <= 60;

-- Who withdrew money on the morning of 28th july 2021?
SELECT people.passport_number FROM atm_transactions
JOIN bank_accounts ON atm_transactions.account_number = bank_accounts.account_number
JOIN people ON bank_accounts.person_id = people.id
WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw";

SELECT * FROM people
JOIN (SELECT caller, duration AS dcaller FROM phone_calls) ON people.phone_number = caller
JOIN (SELECT receiver, year, month, day, duration as dreceiver FROM phone_calls) ON people.phone_number = receiver
WHERE year = 2021 AND month = 7 AND day = 28 AND dcaller <= 60
LIMIT 10;
