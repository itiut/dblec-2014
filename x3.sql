EXPLAIN
SELECT
    AVG(DATEDIFF(o_delivery_date, o_order_datetime))
FROM
    orders;
