# live2d-android

适用于 Android 的 Native 库。

在官方 Cubism Native SDK 基础上封装化简，所有 live2d 操作化简为对 Live2D、Live2D.LAppModel 两个类的操作，并增加额外功能：精确点击判断、部件颜色设定，点击回调和模型参数控制。

可无缝更新官方的 Cubism Framework 和 Core 模块。

使用示例：[MainActivity.kt](./app/src/main/java/com/arkueid/live2d/MainActivity.kt)

添加目标平台架构：  

`build.gradle.kts(Module:app)`

```kotlin
ndk {
    abiFilters.add("arm64-v8a")
//    abiFilters.add("x86")
//    abiFilters.add("x86_64")
}
```