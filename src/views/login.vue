<template>
    <div class="login_div">
        <form method="POST" action="login.php" class="login_form">
            <h1 id="weight">登 录</h1>
            <h1 id="light" @click="gotoRegister">注 册</h1>
            <input type="text" name="userName" placeholder="用户名"/>
            <input type="password" name="passwd" placeholder="密码"/>
            <div class="clearfix"></div>
            <button type="submit">登 录</button>
            <!-- <button @click="gotoTest">测试</button> -->
        </form>
    </div> 
</template>

<script>
export default {
    name: 'Login',
    methods: {
        gotoRegister(){
            this.$router.push({path:'/register',name:'Register'});
        }
    }
}

</script>>
    
<style>
body{
    margin: 0;
}
.clearfix{
    clear: both;
}
.login_div{
    width: 100vw;
    height: 100vh;
    background-color: #0e0b09;
    display: flex;
    align-items: center;
    justify-content: center;
    background-size: cover;
    text-align: center;
}

.login_form{
    width: 320px;
    height: 210px;
    background: rgba(246, 246, 255, 0.9);
    border-radius: 20px;
    position: relative;
    box-shadow:0 0 15px 15px rgba(94, 75, 70, 0.5); 
}
.login_form h1{
    float:left;
    margin: 20px 0 0 62px;
    font-size: 28px;
    color: rgb(43, 46, 40,0.9);
}
#light{
    color: rgb(43, 46, 40,0.3);
}
#light:hover{
    color: rgba(97, 70, 63, 0.9);
}
.login_form input{
    width: 66%;
    height: 24px;
    font-size: 14px;
    margin-top: 15px;
    border: none;
}
.login_form input{
    border: none;
}
.login_form button{
    float: right;
    width: 24%;
    height: 12%;
    margin-top: 18px; 
    margin-right: 50px;
    background-color: rgb(155, 144, 139,0.9);
    border-style: none;
    border-radius: 14.4px ;
    font-weight: bold;
    font-size: 15px;
    color: rgb(43, 46, 40,0.7);
}
.login_form button:hover{
    background-color: rgb(206, 199, 199);
    color: rgb(155,144,139);
}
.login_form button:active{
    border-style: none;
}
#light:hover{
    cursor: pointer;
}
input {
    outline: none;
}
</style>