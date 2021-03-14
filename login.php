<?php
//数据库db_user信息
$servername = "localhost";
$user = "phpmyadminUser";
$password = "U201913354";
$database = "db_user";

//HTML用户登录信息
$userName = $_POST["userName"];
$passwd = $_POST["passwd"];

//连接数据库
$conn = new mysqli($servername, $user, $password, $database);
if ($conn -> connect_error) {
    die("连接失败".$conn->connect_error);
}
echo "连接成功";

$sql = "SELECT * FROM userInfo WHERE userName='$userName'";
$result = $conn -> query($sql);

if ($result -> num_rows > 0) {
    while ($row = $result -> fetch_assoc()) {
        echo $row['userName'];
    }
} else {
    echo "该用户不存在，请先注册";
}

//关闭连接
$conn -> close();
?>