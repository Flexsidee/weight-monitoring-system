<?php
include './db_connection.php'; //includes connection to database 

$value = ""; //initially set the value coming to the api as empty

if ($_SERVER["REQUEST_METHOD"] == "GET") {
    $value = test_input($_GET["value"]); //accept the value from the reqpuest, the requestion was suffixed ?value
   
    $sql = "INSERT INTO data_table (value) VALUES ('" . $value  . "')"; //insert the value gotten into the table "data_table" in the database

    //check if the insertion is successful
    if ($conn->query($sql) === TRUE) {
        echo "New record created successfully";
    } 
    else {
        echo "Error: " . $sql . "<br>" . $conn->error;
    }

    $conn->close();

} else {
    echo "No data posted with HTTP GET."; //if request is not get
}

//this function is used to sanitize user request
function test_input($data) {
    $data = trim($data);
    $data = stripslashes($data);
    $data = htmlspecialchars($data);
    return $data;
}