<template>
  <div id="app">
<div class="line"></div>
<el-menu theme="dark" default-active="1" class="el-menu-demo" mode="horizontal">
  <router-link to="/home"><el-menu-item index="1">Home</el-menu-item></router-link>
  <router-link to="/profile"><el-menu-item index="2">Users</el-menu-item></router-link>
  <router-link to="/contact"><el-menu-item index="3">Contacts</el-menu-item></router-link>
</el-menu>
<router-view></router-view>
  </div>
</template>

<script>
export default {
  name: 'app',
  components: {
  }
}
</script>

<style>
#app {
  font-family: "Helvetica Neue",Helvetica,"PingFang SC","Hiragino Sans GB","Microsoft YaHei","微软雅黑",Arial,sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  color: #2c3e50;

}
</style>
