SELECT * FROM movies
JOIN stars ON movies.id = stars.movie_id
JOIN people ON stars.person_id = people.id
GROUP BY 
LIMIT 10;
WHERE
