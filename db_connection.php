<?php
//setting configuration to the database
$servername = "localhost";
$dbname = "weight_monitoring";
$username = "root";
$password = "";

//start connection to database
$conn = new mysqli($servername, $username, $password, $dbname);

// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 
?>