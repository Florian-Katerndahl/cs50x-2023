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

-- get cars leaving the bakery around time of theft (+/- 10 minutes)
-- +---------------+
-- | license_plate |
-- +---------------+
-- | 5P2BI95       |
-- | 94KL13X       |
-- | 6P58WS2       |
-- | 4328GD8       |
-- | G412CB7       |
-- | L93JTIZ       |
-- | 322W7JE       |
-- | 0NTHK55       |
-- +---------------+
SELECT license_plate FROM bakery_security_logs
WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 5 AND minute <= 25 AND activity = "exit";

-- get people based on license plates
-- +--------+---------+----------------+-----------------+---------------+
-- |   id   |  name   |  phone_number  | passport_number | license_plate |
-- +--------+---------+----------------+-----------------+---------------+
-- | 221103 | Vanessa | (725) 555-4692 | 2963008352      | 5P2BI95       |
-- | 243696 | Barry   | (301) 555-4174 | 7526138472      | 6P58WS2       |
-- | 396669 | Iman    | (829) 555-5269 | 7049073643      | L93JTIZ       |
-- | 398010 | Sofia   | (130) 555-0289 | 1695452385      | G412CB7       |
-- | 467400 | Luca    | (389) 555-5198 | 8496433585      | 4328GD8       |
-- | 514354 | Diana   | (770) 555-1861 | 3592750733      | 322W7JE       |
-- | 560886 | Kelsey  | (499) 555-9472 | 8294398571      | 0NTHK55       |
-- | 686048 | Bruce   | (367) 555-5533 | 5773159633      | 94KL13X       |
-- +--------+---------+----------------+-----------------+---------------+
SELECT * FROM people
WHERE license_plate IN (
    SELECT license_plate FROM bakery_security_logs
    WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 5 AND minute <= 25 AND activity = "exit"
);

-- filter flights taking of one day after theft with at least two pepole boarded from person table where one's license plate was recorderd
-- flight ID 36 has thief and comapgnion
SELECT flights.id FROM flights
JOIN passengers ON flights.id = passengers.flight_id
JOIN people ON passengers.passport_number = people.passport_number
WHERE passengers.passport_number IN (
    SELECT passport_number FROM people
    WHERE license_plate IN (
        SELECT license_plate FROM bakery_security_logs
        WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 5 AND minute <= 25 AND activity = "exit"
    )
) AND flights.year = 2021 AND flights.month = 7 AND flights.day = 29
GROUP BY flights.id
HAVING COUNT(*) >= 2;

-- flight destination of flight on next day
SELECT airports.full_name FROM flights
JOIN airports ON flights.destination_airport_id = airports.id
WHERE flights.id = 36;

-- thief withdrew money
-- either thief or person who helped thief returned
-- number in question: (389) 555-5198
SELECT people.id, people.name, people.phone_number, flights.id FROM atm_transactions
JOIN bank_accounts ON atm_transactions.account_number = bank_accounts.account_number
JOIN people ON bank_accounts.person_id = people.id
JOIN passengers ON people.passport_number = passengers.passport_number
JOIN flights ON passengers.flight_id = flights.id
JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
WHERE
    (atm_transactions.year = 2021 AND atm_transactions.month = 7 AND atm_transactions.day = 28 AND atm_transactions.atm_location = "Leggett Street" AND atm_transactions.transaction_type = "withdraw")
    AND (bakery_security_logs.year = 2021 AND bakery_security_logs.month = 7 AND bakery_security_logs.day = 28 AND bakery_security_logs.hour = 10 AND bakery_security_logs.minute >= 5 AND bakery_security_logs.minute <= 25 AND bakery_security_logs.activity = "exit")
    AND (flights.year = 2021 AND flights.month = 7 AND flights.day = 29)
GROUP BY flights.id
HAVING COUNT(*) >= 2;

-- suspected thief or helper talked on phone with whom?
-- Luca was called by Walter and Kathryn, only ... was also on flight ID 36 to LaGuardia Airport
SELECT * FROM phone_calls
JOIN (SELECT phone_number as caller_num, name as pcaller FROM people) ON caller_num = phone_calls.caller
JOIN (SELECT phone_number as reciever_num, name as pcallee FROM people) ON reciever_num = phone_calls.receiver
WHERE year = 2021 AND month = 7 AND day = 28 AND (caller_num = "(389) 555-5198"OR reciever_num = "(389) 555-5198");


SELECT people.name FROM flights
JOIN passengers ON flights.id = passengers.flight_id
JOIN people ON passengers.passport_number = people.passport_number
WHERE passengers.passport_number IN (
    SELECT passport_number FROM people
    WHERE license_plate IN (
        SELECT license_plate FROM bakery_security_logs
        WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 5 AND minute <= 25 AND activity = "exit"
    )
) AND flights.year = 2021 AND flights.month = 7 AND flights.day = 29 AND flights.id = 36;
