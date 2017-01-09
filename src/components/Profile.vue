<template>
  <div class="profile">
 <el-row>
  <el-col :span="5" v-for="(o, index) in 4" :offset="index > 0 ? 1 : 0">
    <el-card class="profile-card" :body-style="{ padding: '0px' }">
      <img src="..\assets\hamburger.png" class="image">
      <div style="padding: 14px;">
        <span>Name</span>
        <div class="bottom clearfix">
          <time class="time">{{ currentDate }}</time>
          <el-button type="text" class="button">More...</el-button>
        </div>
      </div>
    </el-card>
  </el-col>
</el-row>
  </div>
</template>
<script>
  export default {
    name: 'profile',
    data () {
      return {
        currentDate: new Date()
      }
    }
  }
</script>
<!-- Add "scoped" attribute to limit CSS to this component only -->
<style scoped>
  .profile-card {
    margin: 20px 0 0 20px;
  }

  .time {
    font-size: 13px;
    color: #999;
  }

  .bottom {
    margin-top: 13px;
    line-height: 12px;
  }

  .button {
    padding: 0;
    float: right;
  }

  .image {
    width: 100%;
    display: block;
  }

  .clearfix:before,
  .clearfix:after {
    display: table;
    content: "";
  }

  .clearfix:after {
    clear: both
  }
</style>
