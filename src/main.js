// The Vue build version to load with the `import` command
// (runtime-only or standalone) has been set in webpack.base.conf with an alias.
import Vue from 'vue'
import ElementUI from 'element-ui'
import 'element-ui/lib/theme-default/index.css'
import Router from 'vue-router'
import VueResource from 'vue-resource'

import {routes} from './router-config'
import App from './App'

Vue.use(ElementUI)
Vue.use(Router)
Vue.use(VueResource)

const router = new Router({routes, saveScrollPosition: true})

/* eslint-disable no-unused-vars */
const app = new Vue({
  router,
  render: h => h(App)
}).$mount('#app')
