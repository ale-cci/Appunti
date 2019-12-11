# Advanced MySQL Dogmario++

# Views
Virtual table for database data searches
```sql
CREATE VIEW view_name AS
SELECT field_a, field_b
FROM table_name;
```


# Multiple Table Views
It's possible to build a view using data coming from multiple tables
```sql
CREATE VIEW view_name AS
SELECT field_a, field_b, field_c
FROM table_name
    UNION
SELECT f_a, f_b, f_c
FROM second_table
```
Make sure that the number of column selected in each table is the same


# Indexing
Build a database index for faster search
```sql
CREATE INDEX index_relation_name ON table_name(field_list);
```

# Coalesce
Returns the first non null value
```sql
SELECT COALESCE(name, 'unknown') as name
FROM users
```
Here 'unknown' is returned if the user name is null.


# Cross Join
```sql
SELECT t1.a, t2.b
FROM t1.a
CROSS JOIN t2
```
Performs the cartesian product

