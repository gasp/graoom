#!/usr/local/bin/php
<?php
// run.php for graoom in /home/rannou_s/Work/graoom/test/lists
// 
// Made by Sebastien Rannou
// Login   <rannou_s@epitech.net>
// 
// Started on  Fri Jul  3 22:53:08 2009 Sebastien Rannou
// Last update Sat Sep  5 14:53:59 2009 Sebastien Rannou
//

require_once('../common.php');

$exec = './test';

passthru($exec, $result);

if ($result !== 0)
  nok();
else
  ok();
