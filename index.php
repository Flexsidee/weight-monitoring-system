<?php 
include './db_connection.php';
$sql = "SELECT id, value, datatime FROM data_table ORDER BY id DESC"; //query to fetch all records
?>

<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8" />
    <meta http-equiv="X-UA-Compatible" content="IE=edge" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />

    <!--Include datatabe css  -->
    <link rel="stylesheet" type="text/css" href="./assets/DataTables/datatables.css">

    <!-- Include jquery js -->
    <script src="./assets/jquery3-6-1.js"></script>

    <!-- Include users css  -->
    <link rel="stylesheet" href="./assets/style.css" />

    <title>Weight Monitoring System</title>
</head>

<body>
    <div class="main">
        <div class="main_head">
            <h2 class="heading">Weight Monitoring System</h2>
        </div>

        <div class="main_body">
            <?php 
            $res= mysqli_fetch_assoc(mysqli_query($conn, "SELECT id, value, datatime FROM data_table ORDER BY id DESC LIMIT 1"));
            ?>
            <p class="table-top">
                Last recorded value =
                <span class="value"><?php echo $res['value']; ?>kg</span> on
                <span class="time"><?php echo $res['datatime']; ?>.<span>
            </p>

            <table id="data_table" class="display">
                <thead>
                    <th>S/N</th>
                    <th>Value (in Kg)</th>
                    <th>Date</th>
                </thead>
                <tbody>
                    <?php 
                    if ($result = $conn->query($sql)) {
                        $sn = 0;
                        while ($row = $result->fetch_assoc()) {
                            $sn++;
                            $row_id = $row["id"];
                            $row_value = $row["value"];
                            $row_reading_time = $row["datatime"]; 
                            
                            echo '<tr> 
                                    <td>' . $sn. '</td> 
                                    <td>' . $row_value . '</td> 
                                    <td>' . $row_reading_time . '</td> 
                                    </tr>';
                        }
                        
                        $result->free();
                    }

                    $conn->close();
                ?>
                </tbody>
            </table>

            <button class="refresh-button" onclick="reloadPage()">Refresh Page</button>
        </div>

        <script>
        $(document).ready(function() {
            $("#data_table").DataTable();
        });

        function reloadPage() {
            window.location.reload();
        }
        </script>

        <!-- Include js files -->
        <script type="text/javascript" charset="utf8" src="./assets/DataTables/datatables.js"></script>
</body>

</html>