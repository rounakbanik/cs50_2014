<?php

  // configuration
  require("../includes/config.php"); 
  
  $rows = query("SELECT * FROM history WHERE id = ? ", $_SESSION["id"]);
    
  $positions = [];
  foreach ($rows as $row)
  {
     $positions[] = [
           "transaction" => $row["transaction"],
            "date" => $row["date"],
            "symbol" => $row["symbol"],
            "shares" => $row["shares"],
             "price" => number_format($row["price"],2)
             ];
  }
  
  render("history_form.php", ["positions" => $positions, "title" => "History"]);

?>
