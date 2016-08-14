<?php

  // configuration
    require("../includes/config.php"); 
    
  //if form was submitted
    if($_SERVER["REQUEST_METHOD"] == "POST")
    {
       //validate submission
       if (empty($_POST["symbol"]))
       {
          apologize("You must provide a valid symbol.");
       }
       
       else
       {
          $stock = lookup($_POST["symbol"]);
          
          if($stock === false)
             apologize("You've provided an invalid symbol. Please try again.");
             
            
             
          else
          {
             $name = $stock["name"];
             $symbol = $stock["symbol"];
             $price = $stock["price"];           
             render("quote_price.php", ["name" => $name, "symbol" => $symbol, "price" => $price]);
          }
       
       }
       
    }  
    
    else
    {
       render("quote_form.php");
    }


?>
