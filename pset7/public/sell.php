<?php

   // configuration
   require("../includes/config.php"); 
   
   
   
   
   if($_SERVER["REQUEST_METHOD"] == "POST")
   {
      if(empty($_POST["menu"]))
      {
        apologize("Please select a stock to continue.");
      }
      
      else
      {
        $stock = lookup($_POST["menu"]);  
        
        if($stock === false)
          apologize("Invalid Symbol.");
              
        else
        {
          $shares = query("SELECT * FROM stocks WHERE id = ? AND symbol = ?", $_SESSION["id"], $_POST["menu"]);
        
        
          $value = $stock["price"] * $shares[0]["shares"];
          $transaction = "SELL";
        
          //Update the users table
          query("UPDATE users SET cash = cash + ? WHERE id = ?", $value , $_SESSION["id"]);
        
          //Delete the row from stocks table
          query("DELETE FROM stocks WHERE id = ? AND symbol = ?", $_SESSION["id"], $_POST["menu"]);
          
          query("INSERT INTO history (id, transaction, symbol, shares, price) VALUES(?,?,?,?,?)", $_SESSION["id"], $transaction,
                           $stock["symbol"], $shares[0]["shares"], $stock["price"]);
        
          redirect('/');
        }
        
      }
   
   }
   
   else
   { 
     //Get stock company names from stocks table
     $companies = query("SELECT * FROM stocks WHERE id = ?", $_SESSION["id"]);
     
     render("sell_form.php", ["companies" => $companies]);   
   }  
    



?>
