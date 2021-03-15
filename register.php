<?php
//数据库db_user信息
$servername = "localhost";
$user = "phpmyadminUser";
$password = "U201913354";
$database = "db_user";

//HTML用户注册信息
$names = $_POST["name"];
$userName = $_POST["userName"];
$passwd = $_POST["passwd"];
$email = $_POST["email"];

//连接数据库
$conn = new mysqli($servername, $user, $password, $database);
if ($conn -> connect_error) {
    die("连接失败".$conn->connect_error);
}
echo "连接成功。";

//“用户名”，查询用户名是否存在
$sql_select_userName = "SELECT * FROM userInfo WHERE userName='$userName'";
$result_select_userName = $conn -> query($sql_select_userName);
if ($result_select_userName -> num_rows > 0) {
    echo "该用户名已存在。";
} else {
    //检查两次密码是否一致
    if ($passwd != $repasswd) {
        echo "两次密码不一致。";
    } else {
        //“邮箱”，查询邮箱是否已被注册
        $sql_select_email = "SELECT * FROM userInfo WHERE email='$email'";
        $result_select_email = $conn -> query($sql_select_email);
        if ($result_select_email -> num_rows > 0) {
            echo "该邮箱已被注册。";
        } else {
           //插入注册信息
            $sql = "INSERT INTO userInfo(names,userName,passwd,email) VALUES ('$names','$userName','$passwd','$email')";
            if ($conn -> query($sql) === TRUE) {
                echo "data insert success.";
            } else {
                echo "data insert fail: ".$conn->error;
            } 
        }
    }
}

//关闭连接
$conn -> close();
?>