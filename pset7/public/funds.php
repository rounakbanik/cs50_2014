<?php

  // configuration
  require("../includes/config.php");
  
  if($_SERVER["REQUEST_METHOD"] == "POST") 
  {
    if (empty($_POST["amount"]))
    {
       apologize("PLease fill in an amount");
    }
    
    else if(preg_match("/^\d+$/", $_POST["amount"]) === false)
    {
       apologize("Please enter a non-negative integer as amount");
    }
    
    else
    {
       $value = $_POST["amount"];
       query("UPDATE users SET cash = cash + ? WHERE id = ?", $value , $_SESSION["id"]);
       redirect('/');
    }
  }
  
  else
  {
    render("funds_form.php");
  }  

?>
