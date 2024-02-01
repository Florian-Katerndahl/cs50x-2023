SELECT title, COUNT(*) FROM movies
JOIN stars ON movies.id = stars.movie_id
JOIN people ON stars.person_id = people.id
--WHERE people.name = "Bradley Cooper" AND people.name = "Jennifer Lawrence"
GROUP BY movies.id
LIMIT 10;
