<?php require 'config/db_connect.php'; $r=$conn->query("SELECT * FROM book_logs ORDER BY id DESC"); ?>
<!DOCTYPE html><html><head><link rel="stylesheet" href="assets/style.css"></head><body>
<h2>RFID Library Records</h2><table><tr><th>ID</th><th>Student</th><th>Book</th><th>Scan</th><th>Issue</th><th>Return</th><th>Status</th></tr>
<?php while($row=$r->fetch_assoc()){echo "<tr><td>{$row['id']}</td><td>{$row['Student_Id']}</td><td>{$row['Book_Id']}</td><td>{$row['Scan_Time']}</td><td>{$row['Issue_date']}</td><td>{$row['Return_date']}</td><td>{$row['Status']}</td></tr>";}?>
</table></body></html>