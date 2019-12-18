# MYSQL Cheatsheet
### Domain Creation
```sql
CREATE DOMAIN Age AS SMALLINT
DEFAULT 0
CHECK ( value >= 0 AND value <= 120)
```

### Domain Alteration
```sql
ALTER DOMAIN domain_name
{
    SET DEFAULT default_value |
    DROP DEFAULT |
    ADD CONSTRAINT constraint_definition |
    DROP CONSTRAINT constraint_name
}
```


### Schema Definition
```sql
CREATE TABLE Department
(
    Name        CHAR(20) PRIMARY KEY,
    Address     CHAR(50) NOT NULL,
    SquareKm    SMALLINT,
    City        CHAR(20) DEFAULT "Dallas"
)
```

### Intra-Relational Constraints
```sql
CREATE TABLE person
(
    name    CHARACTER(20) NOT NULL,
    surname CHARACTER(20) NOT NULL,
    UNIQUE (name, surname)
)
```

### Inter-Relational Constraints
```sql
CREATE TABLE employee
(
    register    CHARACTER(6) PRIMARY KEY,
    name        CHARACTER(20) NOT NULL,
    surname     CHARACTER(20) NOT NULL,
    depart      CHARACTER(15)
        REFERENCES department(name),
    salary      NUMERIC(9) DEFAULT 0,

    UNIQUE(name, surname),
    FOREIGN KEY(name, surname)
        REFERENCES registry(name, surname)
)
```

```sql
ON DELETE [CASCADE|SET NULL|SET DEFAULT|NO ACTION]
```

### Table Alteration
```sql
ALTER TABLE table_name ALTER COLUMN attribute_name [SET DEFAULT new_value|DROP DEFAULT];
ALTER TABLE table_name ADD CONSTRAINT constraint_definition;
ALTER TABLE table_name DROP CONSTRAINT constraint_name;
ALTER TABLE table_name ADD COLUMN attribute_name;
ALTER TABLE table_name DROP COLUMN attribute_name;
```


### Deletion
```sql
DROP [SCHEMA|DOMAIN|TABLE|VIEW|ASSERTION] element_name [RESTRICT|CASCADE]
```
`RESTRICT` Does not execute the command on empty objects,
`CASCADE` deletes object and all its dependencies recursively

### Select
```sql
SELECT username AS name
FROM students AS st
WHERE st.age < 25 OR st.surname="red"
```
Select all fields of a table with `table_name.*`

### Join
```sql
SELECT st.name, st.surname, exam.mark
FROM students AS st
JOIN exam ON exam.student_register=st.register
WHERE st.name="bob" OR (st.mark <= 17 AND st.mark <> 3)
```
Other Join are **inner**, **right [outer]**, **left [outer]**, **full [outer]**, **cross** default value is **inner**.

### Like and Null
```sql
SELECT *
FROM employee
WHERE surname LIKE ("ross_" OR "%ossi") AND surname IS NOT NULL
```

### Distinct and Order by
```sql
SELECT DISTINCT name
FROM student
WHERE surname="aleotti"
ORDER BY name [ASC|DESC]
```
Default order is **ascending**, for **descending** order put a `-` in front of the field. Otherwise specify `ASC` or `DESC`.

### Aggregation and Grouping
Available operators are **COUNT**, **SUM**, **MAX**, **MIN**, **AVG**
```sql
SELECT ex.register, AVG(ex.mark) AS mark_avg
FROM exams AS ex
WHERE ex.date = NOW()
GROUP BY register
HAVING mark_avg > 18
```

### Sub-Queries
```sql
SELECT name
FROM employee
[UNION|INTERSECT|EXCEPT|ALL]
    SELECT surname
    FROM employee
```

### Limit and Reverse Order
```sql
SELECT name
FROM employee
ORDER BY -id
LIMIT 10
```
Returns the last 10 added Employee names



### Nested Queries
```sql
SELECT em.name, em.surname
FROM employee em
WHERE dipart = any
(
    SELECT d.name
    FROM department d
    WHERE city="dallas"
)
```
```sql
SELECT st.surname, st.name, ex.teaching
FROM students st, exams ex
WHERE st.register = ex.student
AND ex.date = (
    SELECT MIN(e1.date)
    FROM exams e1
    WHERE e1.student = st.register
)
```

```sql
SELECT *
FROM student st
WHERE exists (
    SELECT *
    FROM students sf
    WHERE st.father=sf.name
)
OR (
    SELECT *
    FROM students sm
    WHERE st.mother=sm.name
)
```

```sql
SELECT *
FROM student st
WHERE (name, surname) IN
(
    SELECT name, surname
    FROM student s1
    WHERE st.age > s1.age
)
```

```sql
SELECT *, (SELECT name FROM student st WHERE st.name='bob')
FROM exam e
```

[more here](https://devhints.io/mysql) and [here](http://www.mysqltutorial.org/mysql-cheat-sheet.aspx)
