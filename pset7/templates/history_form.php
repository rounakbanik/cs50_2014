<div>
    <table class = "table table-striped">
    <tr>
        <td> TRANSACTION </td>
        <td> DATE/TIME </td>
        <td> SYMBOL </td>
        <td> SHARES </td>
        <td> PRICE </td>
    </tr>    
    
    <?php foreach ($positions as $position): ?>

    <tr>
        <td><?= $position["transaction"] ?></td>
        <td><?= $position["date"] ?></td>
        <td><?= $position["symbol"] ?></td>
        <td><?= $position["shares"] ?></td>
        <td>$<?= $position["price"] ?></td>
    </tr>
    <?php endforeach ?>
    </table>
</div>
<div>
    <a href="logout.php">Log Out</a>
</div>
