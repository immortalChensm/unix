<?php
/**
 * Created by PhpStorm.
 * User: 1655664358@qq.com
 * Date: 2019/10/18
 * Time: 17:04
 */

$filePath = $argv[1];

if (posix_mkfifo($filePath,0666)<0){
    fprintf(STDOUT,"命名管道创建错误");
    exit(0);
}

$fd = fopen($filePath,"r");

while (is_resource($fd)){

    $data = fgets($fd);
    if ($data){
        fwrite(STDIN,$data,strlen($data));
    }
}

exit(0);
