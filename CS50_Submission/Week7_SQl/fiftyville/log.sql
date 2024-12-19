-- Keep a log of any SQL queries you execute as you solve the mystery.
--Get the details  of your crime scene
SELECT description
FROM crime_scene_reports
WHERE street = 'Humphrey Street'
AND day = 28
AND month = 7
AND year = 2023;
-- So the the crime took place at 10:15am.Clue:Three witnesses were interviewes
-- Check out the interviews taken
SELECT name,transcript
FROM interviews
WHERE day = 28
AND month = 7
AND year = 2023;
-- Check the security logs as  per witness RUTH
SELECT license_plate
FROM bakery_security_logs
WHERE day = 28
AND month = 7
AND year = 2023
AND activity = 'exit'
AND hour = 10
AND minute BETWEEN 15 AND 30;
--So 8 suspects from here
--From Eugene's statement,check the atm_transactions table
SELECT account_number,amount
FROM atm_transactions
WHERE atm_location = 'Leggett Street'
AND transaction_type = 'withdraw'
AND  year = 2023
AND month = 7
AND  day = 28;
--So 8 account_nos supsected
--From Raymond's evidence phone call records to be fetched
SELECT caller, receiver
FROM phone_calls
WHERE year = 2023
AND month = 7
AND day = 28
AND duration < 60;
--From here 8 numbers under sispect
--Now get the details of the flight from which the suspect travelled
SELECT id
FROM flights
WHERE origin_airport_id = (SELECT id FROM airports WHERE city ='Fiftyville')
AND year = 2023
AND month = 7
AND day = 29
ORDER BY hour ASC,minute ASC LIMIT 1;
--FLight details fetched - 36

                            --FINAL RESULTS--
                            {node.js AND react.js AND }
--Thief
--combine the four sets of suspects
SELECT name
FROM people
WHERE id IN (
    SELECT person_id
    FROM bank_accounts
    WHERE account_number IN
(
            SELECT account_number
            FROM atm_transactions
            WHERE atm_location = 'Leggett Street'
            AND transaction_type = 'withdraw'
            AND  year = 2023
            AND month = 7
            AND  day = 28
                        )
)
AND phone_number IN (
            SELECT caller
            FROM phone_calls
            WHERE year = 2023
            AND month = 7
            AND day = 28
            AND duration < 60
)
AND license_plate IN
(
            SELECT license_plate
            FROM bakery_security_logs
            WHERE day = 28
            AND month = 7
            AND year = 2023
            AND activity = 'exit'
            AND hour = 10
            AND minute BETWEEN 15 AND 30
)
AND passport_number IN (
            SELECT passport_number
            FROM passengers
            WHERE flight_id =
(
                SELECT id
                FROM flights
                WHERE origin_airport_id =
(
                    SELECT id
                    FROM airports
                    WHERE city ='Fiftyville'
                                           )
                AND year = 2023
                AND month = 7
                AND day = 29
                ORDER BY hour ASC,minute ASC
                LIMIT 1
                       )
);
--City escaped to
-- Get this from the flight id
SELECT city
FROM airports
WHERE id = (
    SELECT
    destination_airport_id
    FROM flights
    WHERE origin_airport_id =
(
        SELECT id
        FROM airports
        WHERE city
='Fiftyville'
            )
    AND year = 2023
    AND month = 7
    AND day = 29
    ORDER BY hour ASC,minute ASC
     LIMIT 1
);
--Accomplaince
--Get this from the call records of the main suspect
SELECT name
FROM people
WHERE phone_number = (
    SELECT receiver
    FROM phone_calls
    WHERE year = 2023
    AND month = 7
    AND day = 28
    AND duration < 60
    AND caller =
(
         SELECT phone_number
         FROM people
         WHERE name = 'Bruce'
                            )
);
