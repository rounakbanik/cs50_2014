<?php

  // configuration
  require("../includes/config.php"); 
  
  if ($_SERVER["REQUEST_METHOD"] == "POST")
  {
     if(empty($_POST["symbol"]))
     {
       apologize("Please enter a symbol");
     }
     
     else if(empty($_POST["shares"]))
     {
       apologize("PLease enter number of shares");
     }
     
     else if(preg_match("/^\d+$/", $_POST["shares"]) === false)
     {
       apologize("Please enter a non-negative integer as shares");
     }
     
     else
     {
       $symbol = strtoupper($_POST["symbol"]);
       $shares = lookup($symbol);
       
       if($shares === false)
         apologize("Invalid symbol");
       
       else
       {
         $value = $shares["price"];
         $number = $_POST["shares"];
         $transaction = "BUY";
         
         $money = $value*$number;
         
         $users = query("SELECT * FROM users WHERE id = ?", $_SESSION["id"]);
         $cash = $users[0]["cash"];
         
         if($cash < $money)
           apologize("Not enough funds");
         
         else
         {
           $transaction = 'BUY';
           query("UPDATE users SET cash = cash - ? WHERE id = ?", $money , $_SESSION["id"]);
           query("INSERT INTO stocks (id, symbol, shares) VALUES(?, 
                         ?, ?) ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)", $_SESSION["id"], $shares["symbol"], $number);
           
           query("INSERT INTO history (id, transaction, symbol, shares, price) VALUES(?,?,?,?,?)", $_SESSION["id"], $transaction,
                           $shares["symbol"], $number, $value);
         
           redirect('/');
         }  
         
         
       }  
     }
     
     
  }
  
  else
  {
    render("buy_form.php");
  }
 

?>

