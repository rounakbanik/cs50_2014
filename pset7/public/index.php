<?php

    // configuration
    require("../includes/config.php"); 
    
    //Define the row needed to be implemented
    $rows = query("SELECT * FROM stocks WHERE id = ? ", $_SESSION["id"]);
    
    //Define initial amount
    $user = query("SELECT * FROM users WHERE id = ? ", $_SESSION["id"]);
    
    $positions = [];
    foreach ($rows as $row)
    {
        $stock = lookup($row["symbol"]);
        if ($stock !== false)
        {
            $positions[] = [
                "name" => $stock["name"],
                "price" => number_format($stock["price"],2),
                "shares" => $row["shares"],
                "symbol" => $row["symbol"],
                "total" => number_format($row["shares"]*$stock["price"], 2, ".", ""),
            ];
        }
    }
    
    //Add the balance
    $positions[] = [
                "name" => "",
                "price" => "",
                "shares" => "",
                "symbol" => "CASH",
                "total" => number_format($user[0]["cash"], 2, ".", "")
            ];

    // render portfolio
    render("portfolio.php", ["positions" => $positions, "title" => "Portfolio"]);

?>
