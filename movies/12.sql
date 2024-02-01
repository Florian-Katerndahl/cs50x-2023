SELECT title FROM movies
JOIN stars ON movies.id = stars.movie_id
JOIN people ON stars.person_id = people.id
WHERE stars.person_id IN (people.name = "Bradley Cooper", people.name = "Jennifer Lawrence")
GROUP BY movies.id
LIMIT 10;
