<?php

use Swoole\Process;

Process::signal(SIGALRM, function () {
    static $i = 0;
    echo "#{$i}\talarm\n";
    $i++;
    if ($i > 20) {
        Process::alarm(-1);
    }
});

//100ms
Process::alarm(1000);
