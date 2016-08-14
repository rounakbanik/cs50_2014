<ul class="nav nav-pills">
    <li><a href="quote.php">Quote</a></li>
    <li><a href="funds.php">Funds</a></li>
    <li><a href="buy.php">Buy</a></li>
    <li><a href="sell.php">Sell</a></li>
    <li><a href="history.php">History</a></li>
    <li><a href="logout.php"><strong>Log Out</strong></a></li>
</ul>


<div>
    <table class = "table table-striped">
    <tr>
        <td> SYMBOL </td>
        <td> SHARES </td>
        <td> NAME </td>
        <td> PRICE </td>
        <td> TOTAL </td>
    </tr>    
    
    <?php foreach ($positions as $position): ?>

    <tr>
        <td><?= $position["symbol"] ?></td>
        <td><?= $position["shares"] ?></td>
        <td><?= $position["name"] ?></td>
        <td><?= $position["price"] ?></td>
        <td>$<?= $position["total"] ?></td>
    </tr>
    <?php endforeach ?>
    </table>
</div>
<div>
    <a href="logout.php">Log Out</a>
</div>
