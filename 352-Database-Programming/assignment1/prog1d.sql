SELECT f.fac_name AS faculty_name, s.std_name AS advisee_name
FROM FACULTY f
LEFT JOIN STUDENT s ON f.faculty_id = s.advisor_id
ORDER BY f.fac_name;

SELECT std_name, home_phone
FROM STUDENT
WHERE student_id NOT IN (
    SELECT DISTINCT student_id 
    FROM ENROLLMENT
);


SELECT s.std_name, s.gpa
FROM STUDENT s
WHERE s.gpa = (
    SELECT MAX(gpa) 
    FROM STUDENT 
    WHERE total_credits = s.total_credits
);

SELECT s.std_name, e.course#, e.grade
FROM STUDENT s
JOIN ENROLLMENT e ON s.student_id = e.student_id
WHERE (s.student_id, e.grade) IN (
    SELECT student_id, MIN(grade)
    FROM ENROLLMENT
    GROUP BY student_id
);

SELECT fac_name
FROM FACULTY
WHERE faculty_id NOT IN (
    SELECT DISTINCT advisor_id 
    FROM STUDENT 
    WHERE advisor_id IS NOT NULL
);
