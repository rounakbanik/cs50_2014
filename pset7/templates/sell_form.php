<form action="sell.php" method="post">
    <fieldset>
        <div class="form-group">
            <select autofocus class="form-control" name="menu"/>
                    <option value= ""></option>
                    
                <?php foreach ($companies as $company): ?>
                                        
                       <option value="<?= $company["symbol"] ?>"><?= $company["symbol"] ?></option> 
                    
                <?php endforeach ?>
            </select>
        </div>
        <div class="form-group">
            <button type="submit" class="btn btn-default">Sell</button>
        </div>
    </fieldset>
</form>
