SELECT
    c_last_name, c_first_name
FROM
    customers
WHERE
    EXISTS (
        SELECT
            *
        FROM
            orders, parts
        WHERE
            c_id = o_cid
            AND p_id = o_pid
            AND p_price >= 3000);
