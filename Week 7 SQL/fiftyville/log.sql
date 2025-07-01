-- Keep a log of any SQL queries you execute as you solve the mystery.


-- 1) .schema to understand the database we are working with

.schema



-- 2) We only know the theft took place on July 28, 2024 and that it took place on Humphrey Street
--    Let's start looking into the crime_scene_reports table for that day and street.

SELECT description
FROM crime_scene_reports
WHERE year = 2024
AND month = 7
AND day = 28
AND street LIKE '%Humphrey%';

    -- we got back:
        -- "Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time – each of their interview
        -- transcripts mentions the bakery.



-- 3) We now know we have to check those 3 interviews, that were on the same day and they all mention "Bakery".
--     Lets' check the transcript and names of interviews on that day that mention bakery

SELECT name, transcript
FROM interviews
WHERE transcript LIKE '%bakery%'
AND year = 2024
AND month = 7
AND day = 28;

    -- we got back:
        -- Ruth    | Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot,
        --           you might want to look for cars that left the parking lot in that time frame.
        -- Eugene  | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw
        --           the thief there withdrawing some money.
        -- Raymond | As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the
        --           earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.




-- 4) We now know: a) Thief left the bakery parking lot within 10 minutes (10:15-10:25am) -> we must check 'bakery_security_logs' for $license plate$ and $activity$
--                 b) Before 10:15am, thief was on the 'Legget Street' ATM withdrawing money -> we must check 'atm_transactions' for withdrawals before 10:15am on that day, get $account number$,
--                                                                                           then check 'bank_accounts' $person id$,
--                                                                                           then check 'people' $id/name$.
--                 c) Around 10:15am that day, thief made a call of less than 1min -> we must check 'phone_calls' for $caller$ and $reciever$ with <1min duration, on that day and time
--                 d) Someone bought for them the EARLIEST plane tickets for the following day (29th july 2024) out of Fiftyville
--                                                                                        -> we must check 'flights' and 'airports' to get the $destination$ and 'passengers' $passport$ of flights
--                                                                                           on that day out of Fiftyville, then 'people' for $passport_number$ and $name$ and $license plate$
--


    -- A). Check: 'bakery_security_logs' for $license plate$ and $activity$ to ensure who exited on that day and time

SELECT license_plate, activity
FROM bakery_security_logs
WHERE year = 2024
AND month = 7
AND day = 28
AND hour = 10
AND minute BETWEEN 15 AND 25;

        -- We got back the following suspicious license plates:
        --      +---------------+----------+
        --      | license_plate | activity |
        --      +---------------+----------+
        --      | 5P2BI95       | exit     |
        --      | 94KL13X       | exit     |
        --      | 6P58WS2       | exit     |
        --      | 4328GD8       | exit     |
        --      | G412CB7       | exit     |
        --      | L93JTIZ       | exit     |
        --      | 322W7JE       | exit     |
        --      | 0NTHK55       | exit     |
        --      +---------------+----------+


    -- B) Check:'atm_transactions' for withdrawals before 10:15am on that day, get $account number$ AND bank_accounts' $person id$ AND'people' $id/name$
    --    then 'people' for $passport_number$ and $name$ and $license plate$


SELECT p.name, p.passport_number, p.license_plate, p.phone_number, atm.amount
FROM people AS p
JOIN bank_accounts AS ba ON p.id = ba.person_id
JOIN atm_transactions AS atm ON ba.account_number = atm.account_number
WHERE atm.year = 2024
AND atm.month = 7
AND atm.day = 28
AND atm.transaction_type LIKE '%withdraw%'
AND atm.atm_location LIKE '%Legget%';

        -- We got back the following:
        --      +---------+-----------------+---------------+----------------+--------+
        --      |  name   | passport_number | license_plate |  phone_number  | amount |
        --      +---------+-----------------+---------------+----------------+--------+
        --      | Bruce   | 5773159633      | 94KL13X       | (367) 555-5533 | 50     | license plate checks, possible thief
        --      | Diana   | 3592750733      | 322W7JE       | (770) 555-1861 | 35     | license plate checks, possible thief
        --      | Brooke  | 4408372428      | QX4YZN3       | (122) 555-4581 | 80     | no check
        --      | Kenny   | 9878712108      | 30G67EN       | (826) 555-1652 | 20     | no check
        --      | Iman    | 7049073643      | L93JTIZ       | (829) 555-5269 | 20     | license plate checks, possible thief
        --      | Luca    | 8496433585      | 4328GD8       | (389) 555-5198 | 48     | no check
        --      | Taylor  | 1988161715      | 1106N58       | (286) 555-6063 | 60     | no check
        --      | Benista | 9586786673      | 8X428L0       | (338) 555-6650 | 30     | no check
        --      +---------+-----------------+---------------+----------------+--------+


-- C) Check: 'phone_calls' for $caller$ and $reciever$ with <1min duration, on that day and time
SELECT caller, receiver
FROM phone_calls
WHERE year = 2024
AND month = 7
AND day = 28
AND duration <= 60;

                -- We got back:
                --      +----------------+----------------+
                --      |     caller     |    receiver    |
                --      +----------------+----------------+
                --      | (130) 555-0289 | (996) 555-8899 | no check
                --      | (499) 555-9472 | (892) 555-8872 | no check
                --      | (367) 555-5533 | (375) 555-8161 | caller phone (BRUCE) nº checks, possible thief
                --      | (609) 555-5876 | (389) 555-5198 | no check
                --      | (499) 555-9472 | (717) 555-1342 | no check
                --      | (286) 555-6063 | (676) 555-6554 | no check
                --      | (770) 555-1861 | (725) 555-3243 | caller phone (DIANA) nº checks, possible thief
                --      | (031) 555-6622 | (910) 555-3251 | no check
                --      | (826) 555-1652 | (066) 555-9701 | no check
                --      | (338) 555-6650 | (704) 555-2131 | no check
                --      +----------------+----------------+
                --
                -- We know now the Thief is either Bruce or Diana, and also the possible accomplice's phone number (Receiver)

        -- We need to know the receiver's name and passport number

SELECT name, passport_number, phone_number
FROM people
WHERE phone_number IN ('(375) 555-8161', '(725) 555-3243')

                -- We got back:
                --      +--------+-----------------+----------------+
                --      |  name  | passport_number |  phone_number  |
                --      +--------+-----------------+----------------+
                --      | Philip | 3391710505      | (725) 555-3243 |
                --      | Robin  | NULL            | (375) 555-8161 |
                --      +--------+-----------------+----------------+
                -- Now we know BRUCE spoke with ROBIN, DIANA spoke with PHILIP,
                -- So the receiver, and accomplice, is either Philip or Robin

    -- D). Check:'flights' and 'airports' to get the $destination$ and 'passengers' $passport$ of flights on that day out of Fiftyville,

SELECT air.full_name, air.city, air2.full_name, air2.city, pass.passport_number, pe.name, fli.hour, fli.minute
FROM airports AS air
JOIN flights AS fli ON fli.origin_airport_id = air.id
JOIN airports AS air2 ON fli.destination_airport_id = air2.id
JOIN passengers AS pass ON pass.flight_id = fli.id
JOIN people AS pe ON pe.passport_number = pass.passport_number
WHERE fli.origin_airport_id = (
    SELECT id
    FROM airports
    WHERE city LIKE '%Fiftyville%'
    )
AND fli.year = 2024
AND fli.month = 7
AND fli.day = 29
AND pass.passport_number IN (5773159633, 3592750733, NULL)


                -- We got back:
                --      +-----------------------------+------------+-----------------------------+---------------+-----------------+-------+------+--------+
                --      |          full_name          |    city    |          full_name          |     city      | passport_number | name  | hour | minute |
                --      +-----------------------------+------------+-----------------------------+---------------+-----------------+-------+------+--------+
                --      | Fiftyville Regional Airport | Fiftyville | Logan International Airport | Boston        | 3592750733      | Diana | 16   | 0      |
                --      | Fiftyville Regional Airport | Fiftyville | LaGuardia Airport           | New York City | 5773159633      | Bruce | 8    | 20     |
                --      +-----------------------------+------------+-----------------------------+---------------+-----------------+-------+------+--------+

                -- We now know the Thief was either Bruce (5773159633) and the accomplice Robin (No passport). Can't be Diana, not the earliest flight nor same city.
