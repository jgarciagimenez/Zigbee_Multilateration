 <?php

$servername = "127.0.0.1";
$username = "root";
$password = "";
$dbname = "coordenadas";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}


$sql = "SELECT id, x, y FROM coor ORDER BY id DESC LIMIT 1";
$result = $conn->query($sql);

if ($result->num_rows > 0) {
    // output data of each row
    while($row = $result->fetch_assoc()) {
        echo $row["x"] ." ". $row["y"] ;
    }
} else {
    echo "0 results";
}
$conn->close();


?> 
