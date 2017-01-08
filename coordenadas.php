
<?php
	$servername = "localhost";
	$username = "root";
	$password = "";
	$dbname = "coordenadas";

	$conn = mysqli_connect($servername, $username, $password, $dbname);


	$sql = "SELECT id, x, y FROM coor ORDER BY id DESC LIMIT 1";
	$result = $conn->query($sql);

	if ($result->num_rows > 0) {
    	// output data of each row
	echo "";
    	while($row = $result->fetch_assoc()) {
		$salida = $row["x"]. " " . $row["y"];
    		echo ($salida);
	}
	} else {
    		echo "0 results";
	}
	$conn->close();
?>
