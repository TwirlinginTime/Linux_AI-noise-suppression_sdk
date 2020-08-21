
# 拓灵AI降噪使用文档

## 使用说明
1. 进入`samples`目录，打开命令行界面执行`. ./64bit_make.sh`(注意两个`.`之间需要加入空格)完成编译。
2. 编译完成后进入`bin`目录，其中生成了`twirlingCaptureSample`可执行程序，和一个示例音频`music.pcm`,以此音频为例命令行输入`./twirlingCaptureSample music.pcm music_after.pcm`即可将`music.pcm`音频进行AI降噪处理，如果需要处理别的音频请相应替换文件名，命令格式`./twirlingCaptureSample input.pcm/input.raw out.pcm/out.raw`（注意音频文件必须为pcm格式或raw格式，且16K采样率）