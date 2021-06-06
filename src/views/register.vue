<template>
    <div class="register_div">
        <form method="POST" action="register.php" class="register_form">
            <h1 id="light" @click="gotoLogin">登 录</h1>
            <h1 id="weight">注 册</h1>
            <input type="text" id="nm" name="name" placeholder="请输入真实姓名"
                v-model="name" @blur='nameCheck' @focus="spanClear(1)"/>
            <br><span id="nmError">{{ tip1 }}</span>
            <input type="text" id="usname" name="userName" maxlength="16" placeholder="请输入用户名"
                v-model="username" @mouseover="inputTip(2)" @mouseleave='spanClear(2)' @blur="usernameCheck" @focus="spanClear(2)"/>
            <br><span id="nameError">{{ tip2 }}</span>
            <input type="password" id="userpwd" name="passwd" maxlength="18" placeholder="请输入密码"
                v-model="password" @mouseover="inputTip(3)" @mouseleave='spanClear(3)' @blur="passwordCheck" @keyup="strengthCheck" @focus="spanClear(3)"/>
            <span id="check">{{ passwordStrength }}</span><br><span id="upwdError">{{ tip3 }}</span>
            <input type="password" id="confirmpwd" name="repasswd" maxlength="18" placeholder="确认密码"
                v-model="confirmPassword" @blur="passwordConfirm" @focus="spanClear(4)"/>
            <br><span id="pwdError">{{ tip4 }}</span>
            <input type="email" id="eml" name="email" placeholder="请输入常用邮箱"
                v-model="email" @blur="emailCheck" @focus="spanClear(5)"/>
            <div id="emlError">{{ tip5 }}</div>
            <div class="clearfix"></div>
            <button id="btn" @click="submit">注 册</button>
        </form>
    </div>
</template>

<script>
export default {
    name: 'Register',
    data(){
        return {
            name: '',
            tip1: '',
            username: '',
            tip2: '',
            password: '',
            passwordStrength: '',
            tip3: '',
            confirmPassword: '',
            tip4: '',
            email: '',
            tip5: '',
        }
    },
    methods: {
        gotoLogin(){
            this.$router.push({path:'/login', name:'Login'})
        },
        nameCheck(){
            var nmExp = /(^[\u4e00-\u9fa5]{1}[\u4e00-\u9fa5·。]{0,10}[\u4e00-\u9fa5]{1}$)|(^[a-zA-Z]{1}[a-zA-Z\s]{0,20}[a-zA-Z]{1}$)/;
			var ok1 = nmExp.test(this.name)
            if(this.name == ''){
                this.tip1 = '真实姓名不能为空';
            }else{
                if(ok1){
					this.tip1 = '';
				}else{
					this.tip1 = '姓名格式不正确';
				}
            }
        },
        usernameCheck(){
            var unmExp =  /[0-9A-Za-z]{8,16}/
			var ok2 = unmExp.test(this.username);
            if(this.username == ''){
                this.tip2 = '用户名不能为空'
            }else{
                if(ok2){
                    this.tip2 = '';
                }else{
                    this.tip2 = '用户名格式不正确';
                }
            }

        },
        passwordCheck(){
            var upwdExp = /[0-9A-Za-z]{6,18}/
			var ok3 = upwdExp.test(this.password);
            if(this.password == ''){
                this.tip3 = '密码不能为空';
            }else{
                if(ok3){
                    this.tip3 = '';
                }else{
                    this.tip3 = '密码格式不正确';
                }
            }
            
        },
        strengthDefine(value) {
            var modes = 0;
			if(value.length < 6){//最初级别
				return modes;
			}
			if(/\d/.test(value)){//如果用户输入的密码 包含了数字
				modes++;
			}
			if(/[a-z]/.test(value)){//如果用户输入的密码 包含了小写的a到z
				modes++;
			}
			if(/[A-Z]/.test(value)){//如果用户输入的密码 包含了大写的A到Z
				modes++;
			}
			switch(modes){
				case 1 :
				return 1;
				case 2 :
				return 2;
				case 3 :
				return 3;
			}
        },
        strengthCheck() {
            var pwdExp = /^[A-Za-z0-9]+$/;
			var ok3 = pwdExp.test(this.password);
			if(ok3){
				this.tip3 = '';
				var index = this.strengthDefine(this.password);
				if(index == 1){
					this.passwordStrength = '弱';
				}else if(index == 2){
					this.passwordStrength = '中';
				}else if(index == 3){
					this.passwordStrength = '强';
				}
			}else{
				this.passwordStrength = '';
				this.tip3 = "密码不符合规定";
			}
        },
        passwordConfirm() {
            if( (this.confirmPassword != this.password) || this.confirmPassword == '' ){
                this.tip4 = '确认密码和密码不一致';
            }else{
                this.tip4 = '';
            }
        },
        emailCheck() {
            if(this.email == ""){
				this.tip5 = '邮箱不能为空';
			}else{
				var emlExp = /^\w+([-+.]\w+)*@\w+([-.]\w+)*\.\w+([-.]\w+)*/
				var ok4 = emlExp.test(this.email);
				if(ok4){
					this.tip5 = '';
				}else{
					this.tip5 = '邮箱格式不正确';
                }
			}
        },
        inputTip(index) {
            switch(index){
                case 2:
                    this.tip2 = '数字+字母（区分大小写），长度8-16位';
                    break;
                case 3:
                    this.tip3 = '数字、字母（区分大小写），长度6-18位';
            }
        },
        spanClear(index) {
            switch(index){
                case 1:
                    this.tip1 = '';
                    break;
                case 2:
                    this.tip2 = '';
                    break;
                case 3:
                    this.tip3 = '';
                    break;
                case 4:
                    this.tip4 = '';
                    break;
                case 5:
                    this.tip5 = '';
                    break;
            }
        },
        submit() {
            if(this.tip1==''&&this.tip2==''&&this.tip3==''&&this.tip4==''&&this.tip5==''){
                //document.getElementById('btn').submit();
            }
        }
    }
}

</script>

<style>
body{
    margin: 0;
}
.clearfix{
    clear: both;
}
.register_div{
    width: 100vw;
    height: 100vh;
    background-color: #0e0b09;
    display: flex;
    align-items: center;
    justify-content: center;
    background-size: cover;
    text-align: center;
}
.register_form{
    width: 320px;
    height: 360px;
    background: rgba(246, 246, 255, 0.9);
    border-radius: 20px;
    position: relative;
    box-shadow:0 0 15px 15px rgba(94, 75, 70, 0.5);
}
.register_form h1{
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
.register_form input{
    width: 66%;
    height: 24px;
    font-size: 14px;
    margin-top: 22px;
    border: none;
}
.register_form input{
    border: none;
}
.register_form button{
    float: right;
    width: 24%;
    height: 28.8px;
    margin-top: 18px; 
    margin-right: 50px;
    background-color: rgb(155, 144, 139,0.9);
    border-style: none;
    border-radius: 14.4px ;
    font-weight: bold;
    font-size: 15px;
    color: rgb(43, 46, 40,0.7);
}
.register_form button:hover{
    background-color: rgb(206, 199, 199);
    color: rgb(155,144,139);
}
.register_form button:active{
    border-style: none;
}
#nmError, #nameError, #upwdError, #pwdError, #emlError {
	position: fixed;
    font-size: 14px;
}
#emlError {
    margin-left: 54px;
}
#check {
    position: fixed;
    margin-left: 6px;
    margin-top: 23px;
}
input {
    outline: none;
}
</style>