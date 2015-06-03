/**********************************************************************
* 文件名称：ch_tmpfile.c
* 内容摘要：将临时文件转换为正式文件
* 作    者：gehu
* 完成日期：2015-01-30
**********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
// 函数声明
int save_content_to_file(char *filename, char *content);
 
/*
* test main
*/
int main()
{
    int flag = 0;       // 是否要将临时文件转换为正式文件: 1-要,0-不
    int ret = 0;        // 调用写文件函数后的返回值
    char tmp_filename[100]   = {0};     // 用于存放带路径的临时文件名
    char normal_filename[100] = {0};    // 用于存放带路径的正式文件名
    char content[100] = {0};            // 用于存放写入文件的内容
    char command_buff[500] = {0};       // 用于存放转换文件的命令
 
    strcpy(tmp_filename,   "testfile_temp.txt");
    strcpy(normal_filename, "testfile.txt");
    strcpy(content, "hello, world!");
    
    // 将内容写入临时文件
    flag = save_content_to_file(tmp_filename, content);
    if (flag != 0){
      printf("Save '%s' to '%s' failed!\n", content, tmp_filename);
      return -1;
    }else{
      printf("Save '%s' to '%s' successfully!\n", content,tmp_filename);
    }

    // 读入控制是否将临时文件转换为正式文件的标志
    printf("Is ready to change temp file to normal file? (1-Yes, 0-No):\t");
    scanf("%d", &flag);
 
    // 根据标志判断是否将临时文件转换为正式文件
    if (flag == 1){
      printf("Now, begin to change '%s' to '%s'!\n", tmp_filename, normal_filename);
      snprintf(command_buff, sizeof(command_buff) - 1, "mv %s %s", tmp_filename, normal_filename);
      system(command_buff);  //调用系统命令
    }else{
      printf("Don't change '%s' to '%s'!\n", tmp_filename, normal_filename);
    }
 
   return 0; 
}
 
 
/**
 * 保存内容到临时文件中
 * @param  filename 临时文件的文件明
 * @param  content  追加的内容
 * @return          成功返回1，否则返回0
 */
int save_content_to_file(char *filename, char *content)
{
   FILE *fp = NULL;
 
   if (filename == NULL || content == NULL)
   {
       printf("SaveContentToFile: input parameter(s) is NULL!\n");
       return -1;
   }
 
   fp = fopen(filename, "ab");     // 打开文件, 每次写入的时候在后面追加
   if (fp == NULL)
   {
       printf("SaveContentToFile: save '%s' to file '%s' failed!\n", content, filename);
       return -1;
   }
 
   fprintf(fp, "%s", content);
 
   fflush(fp);     // 刷新文件
   fclose(fp);
   fp = NULL;     // 将文件指针置为空
 
   return 0;
}