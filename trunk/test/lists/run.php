#!/usr/local/bin/php
<?php
// run.php for graoom in /home/rannou_s/Work/graoom/test/lists
// 
// Made by Sebastien Rannou
// Login   <rannou_s@epitech.net>
// 
// Started on  Fri Jul  3 22:53:08 2009 Sebastien Rannou
// Last update Fri Jul  3 23:09:09 2009 Sebastien Rannou
//

$handle = opendir("/bin/");

$exec = "./lists ";

while (($item = readdir($handle)))
  {
    $exec .= $item . " ";
  }

passthru($exec, $result);

if ($result !== 0)
  echo "Test NOK\n";
else
  echo "Test OK\n";
