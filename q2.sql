SELECT
    c_last_name, c_first_name
FROM
    customers
WHERE
    SUBSTRING(c_zipcode, 1, 2) = ALL (
        SELECT
            SUBSTRING(b_zipcode, 1, 2)
        FROM
            branches,
            orders
        WHERE
            c_id = o_cid
            AND b_id = o_bid);
