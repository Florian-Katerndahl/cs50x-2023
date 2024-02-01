SELECT title FROM movies
JOIN stars ON movies.id = stars.movie_id
WHERE stars.person_id IN (
    SELECT id FROM people
    WHERE name = "Bradley Cooper" OR name = "Jennifer Lawrence"
    )
GROUP BY movies.id
LIMIT 10;
