<?php
// run.php for graoom in /home/rannou_s/Work/graoom/test/lists
// 
// Made by Sebastien Rannou
// Login   <rannou_s@epitech.net>
// 
// Started on  Fri Jul  3 22:53:08 2009 Sebastien Rannou
// Last update Sat Sep  5 18:19:27 2009 Sebastien Rannou
//

require_once('../common.php');

if (($handle = opendir("examples")))
  {
    while (($path = readdir($handle)))
      {
	if ($path[0] != ".")
	  {
	    $fp = "./examples/" . $path;
	    $array = parse_ini_file($fp);
	    foreach ($array as $key => $value)
	      {
		passthru("./test " . $fp . " " . $key . " " . $value, $result);
		if ($result !== 0)
		  nok();
		else
		  ok();
	      }
	  }
      }
  }
