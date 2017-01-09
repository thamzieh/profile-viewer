<template>
  <div id="app">
<div class="line"></div>
<el-menu theme="dark" default-active="1" class="el-menu-demo" mode="horizontal">
  <router-link to="/home"><el-menu-item index="1">Home</el-menu-item></router-link>
  <router-link to="/profile"><el-menu-item index="2">Profiles</el-menu-item></router-link>
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
  font-family: 'Avenir', Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #2c3e50;

}
</style>
