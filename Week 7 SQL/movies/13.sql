SELECT DISTINCT name
FROM people
JOIN stars ON people.id = stars.person_id -- link people to stars to know stars's names
JOIN movies ON stars.movie_id = movies.id -- link stars to movies to know stars's movies
WHERE movies.id IN -- query for the name of people that starred in the movies where Kevin Bacon from 1958 starred
    (SELECT movie_id FROM stars
    JOIN people ON stars.person_id = people.id
    WHERE name = 'Kevin Bacon' AND birth = 1958) -- subquery for list of movie id's where Kevin Bacon from 1958 starred
AND name != 'Kevin Bacon'; -- exclude Kevin Bacon from the return
