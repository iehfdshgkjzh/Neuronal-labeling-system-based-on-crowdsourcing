<?php
//数据库db_user信息
$servername = "localhost";
$user = "phpmyadminUser";
$password = "U201913354";
$database = "db_user";

//HTML用户注册信息
$name = $_POST["name"];
$userName = $_POST["userName"];
$passwd = $_POST["password"];
$email = $_POST["email"];

//连接数据库
$conn = new mysqli($servername, $user, $password, $database);
if ($conn -> connect_error) {
    die("连接失败".$conn->connect_error);
}
echo "连接成功";

//插入注册信息
$sql = "insert into userInfo(name,userName,passwd,email) values ('$name','$userName','$passwd','$email')";
if ($con -> query($sql) === true) {
    echo "data insert success";
} else {
    echo "data insert fail".$con->error;
}

//关闭连接
$conn -> close();
?>