#!/bin/bash

#源文件夹
sourceFolder="/home/parallels/Desktop/linux第一次实验"

#目标文件夹
aidFolder="/home/parallels/Desktop/Aid"

#分析文件
analy="/home/parallels/Desktop/Aid/analysis.txt"

#创建目标文件夹
ifFolder="${aidFolder}"
#判断是否存在文件夹
if [ ! -d $ifFolder ];then
#若不存在则创建
 mkdir $ifFolder
else
#否则为文件增加随机后缀
   elseFolder="${aidFolder}_$RANDOM"
   mkdir $elseFolder
fi

cd /home/parallels/Desktop/linux第一次实验
#用数组遍历源文件夹中的文件
filePath='ls *'
fileArray=(${filePath// / })
unset fileArray[0]
for file in ${fileArray[@]}
do
  #用文件后缀命名，在目标文件夹中创建分类文件夹
  filename="${file##*.}"
  nameFolder="$aidFolder/$filename"
  if [ ! -d $nameFolder ];then
     mkdir $nameFolder
  else
     elsename="${nameFolder}_$RANDOM"
     mkdir $elsename
  fi 
  #复制文件到对应的分类文件夹
  count=0
  sourcePath="$sourceFolder/$file"
  goalPath="$nameFolder/$file"
  newPath=$goalPath
while [ -f $newPath ]
  do
     let count+=1
     newPath="${goalPath%%.*}.$count.${filename}"
  done
  cp $sourcePath $newPath
  echo "$sourcePath,$newPath,$filename">>$analy
done

column -t $analy



