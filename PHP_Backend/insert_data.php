<?php
require_once '../config/db_connect.php';
require_once 'issue_return.php';
$student_id=$_POST['student_id']??'';
$book_id=$_POST['book_id']??'';
$scan_time=$_POST['scan_time']??date('Y-m-d H:i:s');
$issue_date=$_POST['issue_date']??date('Y-m-d');
processTransaction($conn,$student_id,$book_id,$scan_time,$issue_date);
$conn->close();
?>