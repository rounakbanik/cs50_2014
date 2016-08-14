<?php

    // configuration
    require("../includes/config.php");

    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if(empty($_POST["username"]))
        {
           apologize("You must provide a username.");
        }
        
        else if(empty($_POST["password"]))
        {
           apologize("You must provide a password.");
        }
        
        else if(empty($_POST["confirmation"]))
        {
           apologize("Please confirm password.");
        }
        
        else if($_POST["password"] !== $_POST["confirmation"])
        {
           apologize("Password and confirmation do not match.");
        }
        
        $result = query("INSERT INTO users (username, hash, cash) VALUES(?, ?, 10000.00)", $_POST["username"], crypt($_POST["password"]));
          
        
        if($result === false)
           apologize("Registration failed. Username already exists.");
        else
        {
           $rows = query("SELECT LAST_INSERT_ID() AS id");
           $id = $rows[0]["id"];
           $_SESSION["id"] = $id;
           redirect("/");
           
        }
    }
    else
    {
        // else render form
        render("register_form.php", ["title" => "Register"]);
    }

?>
