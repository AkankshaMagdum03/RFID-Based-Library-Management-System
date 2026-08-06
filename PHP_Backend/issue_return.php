<?php
function processTransaction($conn,$student_id,$book_id,$scan_time,$issue_date){
$q="SELECT * FROM book_logs WHERE Student_Id='$student_id' AND Book_Id='$book_id' ORDER BY id DESC LIMIT 1";
$r=$conn->query($q);
if($r && $r->num_rows){
$row=$r->fetch_assoc();
if($row['Status']=='Issued'){
$d=date('Y-m-d');
$conn->query("UPDATE book_logs SET Return_date='$d',Status='Returned' WHERE id=".$row['id']);
echo 'Book returned successfully';
}else{
$conn->query("INSERT INTO book_logs(Student_Id,Book_Id,Scan_Time,Issue_date,Status) VALUES('$student_id','$book_id','$scan_time','$issue_date','Issued')");
echo 'Book issued successfully';
}}else{
$conn->query("INSERT INTO book_logs(Student_Id,Book_Id,Scan_Time,Issue_date,Status) VALUES('$student_id','$book_id','$scan_time','$issue_date','Issued')");
echo 'Book issued successfully';
}}
?>