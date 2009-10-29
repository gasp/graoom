<?php
// run.php for battletrantor in /home/rannou_s/Work/graoom/test/lists
// 
// Made by Sebastien Rannou
// Login   <rannou_s@epitech.net>
// 
// Started on  Fri Jul  3 22:53:08 2009 Sebastien Rannou
// Last update Sat Sep  5 15:17:34 2009 Sebastien Rannou
//

require_once('../common.php');

$handle = opendir("/bin/");

$exec = "./lists ";

while (($item = readdir($handle)))
  {
    $exec .= $item . " ";
  }

passthru($exec, $result);

if ($result !== 0)
  nok();
else
  ok();
