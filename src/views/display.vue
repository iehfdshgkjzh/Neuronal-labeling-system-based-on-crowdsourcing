<template>
<a-layout>
  <a-layout-content class="content">
    <a-col :span="11" class="content-left">
      <div class="spin-container" v-if="isLoadingImg">
        <a-spin>
          <a-icon slot="indicator" type="loading" style="font-size: 24px" spin />
        </a-spin>
      </div>

      <div class="img-holder">
        <img  class="filter-image" ref="img" :style="{ filter: `blur(${filter.blur}px) brightness(${filter.brightness}) contrast(${filter.contrast}%) grayscale(${filter.grayscale}%) hue-rotate(${filter.hueRotate}deg) invert(${filter.invert}%) opacity(${filter.opacity}%) saturate(${filter.saturate}%`}">
      </div>
      <a-col :span="24" class="filter-buttons">
        <a-button-group>
          <a-button type="default" icon="upload" @click="upload">上传</a-button>
          <a-button type="danger" icon="sync" @click="reset">重置</a-button>
        </a-button-group>
      </a-col>
    </a-col>
    <a-col :span="11">
      <a-form class="filter-form">
        <a-form-item label='亮度' :labelCol="{ span: 4 }" :wrapperCol="{ span: 20 }">
          <a-col class="m-r-12px" :span="19">
            <a-slider :min="0" :max="1" :step="0.1" v-model="filter.brightness" />
          </a-col>
          <a-col :span="4">
            <a-input-number :min="0" :max="1" :step="0.1" v-model="filter.brightness" />
          </a-col>
        </a-form-item>
        <a-form-item label='对比度' :labelCol="{ span: 4 }" :wrapperCol="{ span: 20 }">
          <a-col class="m-r-12px" :span="19">
            <a-slider :min="0" :max="1000" :step="1" v-model="filter.contrast" />
          </a-col>
          <a-col :span="4">
            <a-input-number :min="0" :max="1000" :step="1" v-model="filter.contrast" />
          </a-col>
        </a-form-item>
        <a-form-item label='灰度' :labelCol="{ span: 4 }" :wrapperCol="{ span: 20 }">
          <a-col class="m-r-12px" :span="19">
            <a-slider :min="0" :max="100" :step="1" v-model="filter.grayscale" />
          </a-col>
          <a-col :span="4">
            <a-input-number :min="0" :max="100" :step="1" v-model="filter.grayscale" />
          </a-col>
        </a-form-item>

        <a-form-item label='透明度' :labelCol="{ span: 4 }" :wrapperCol="{ span: 20 }">
          <a-col class="m-r-12px" :span="19">
            <a-slider :min="0" :max="100" :step="1" v-model="filter.opacity" />
          </a-col>
          <a-col :span="4">
            <a-input-number :min="0" :max="100" :step="1" v-model="filter.opacity" />
          </a-col>
        </a-form-item>

        <a-form-item label='饱和度' :labelCol="{ span: 4 }" :wrapperCol="{ span: 20 }">
          <a-col class="m-r-12px" :span="19">
            <a-slider :min="0" :max="100" :step="1" v-model="filter.saturate" />
          </a-col>
          <a-col :span="4">
            <a-input-number :min="0" :max="100" :step="1" v-model="filter.saturate" />
          </a-col>
        </a-form-item>
      </a-form>
    </a-col>
  </a-layout-content>
</a-layout>
</template>

<script>
import { Chrome } from 'vue-color'
export default {
    name: "Display",
    components: {
      'chrome-picker': Chrome
    },
    data() {
      return {
        quality: 1,
        isLoadingImg: false,
        imgName: '',
        filter: {
          blur: 0,
          brightness: 1,
          contrast: 100,
          grayscale: 0,
          hueRotate: 0,
          invert: 0,
          opacity: 100,
          saturate: 100
        }
      }
    },
    computed: {
      filterStr() {
        return `.filter-image { 
          filter: blur(${this.filter.blur}px) brightness(${this.filter.brightness}) contrast(${
          this.filter.contrast
        }%) grayscale(${this.filter.grayscale}%) hue-rotate(${this.filter.hueRotate}deg) 
        invert(${this.filter.invert}%) opacity(${this.filter.opacity}%) saturate(${
          this.filter.saturate
        }%); 
      }`
      }
    },
    methods: {
      upload(info) {
        this.reset();
        const self = this
        const filterImg = this.$refs.img
        const input = document.createElement('input')
        input.type = 'file'
        input.multiple = false
        input.accept = '.png, .jpg, .jpeg'
        input.addEventListener('abort', () => (this.isLoadingImg = false))
        input.addEventListener(
          'change',
          function(event) {
            self.isLoadingImg = true
            const file = this.files[0]
            const imgSrc = window.URL.createObjectURL(file)
            self.imgName = file.name

            filterImg.src = imgSrc
            filterImg.addEventListener('load', function() {
              self.isLoadingImg = false
              window.URL.revokeObjectURL(this.src)
            })
          },
          false
        )
        input.click()
      },
      updateFilterColor(event) {
        this.filter.color = event.hex8
      },
      reset() {
        this.filter = {
          blur: 0,
          brightness: 1,
          contrast: 100,
          grayscale: 0,
          hueRotate: 0,
          invert: 0,
          opacity: 100,
          saturate: 100,
        }
      },
    }
}
</script>

<style>
.header {
  display: flex;
  justify-content: space-between;
  align-items: center;
  color: #fff;
  height: 40px;
}

.link {
  color: #fff;
}

.content {
  min-height: calc(100vh - 40px);
  display: flex;
  align-items: flex-start;
  justify-content: space-between;
}

.spin-container {
  position: absolute;
  top: 0;
  left: 0;
  display: flex;
  justify-content: center;
  align-items: center;
  width: 100%;
  height: 400px;
  background-color: rgba(0, 0, 0, 0.15);
}

.img-holder {
  width: 100%;
  min-height: 400px;
  border: 1px solid #eee;
  line-height: 0;
  margin: 24px;
  margin-top: 12px;
  background-color: #fff;
}

.filter-image {
  width: 100%;
  max-height: 640px;
  border-radius: 4px;
  border: none;
}

.filter-text {
  width: 100%;
  margin: 24px;
}

.filter-buttons {
  display: flex;
  justify-content: center;
  align-items: center;
}

.filter-form {
  margin: 12px;
  padding: 12px;
  background-color: #fff;
}

.ant-form-item {
  margin-bottom: 4px;
}

.m-r-12px {
  margin-right: 12px;
}
</style>
