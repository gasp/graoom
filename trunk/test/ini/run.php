#!/usr/local/bin/php
<?php
// run.php for graoom in /home/rannou_s/Work/graoom/test/lists
// 
// Made by Sebastien Rannou
// Login   <rannou_s@epitech.net>
// 
// Started on  Fri Jul  3 22:53:08 2009 Sebastien Rannou
// Last update Sat Jul  4 12:54:05 2009 Sebastien Rannou
//

if (($handle = opendir("examples")))
  {
    while (($path = readdir($handle)))
      {
	if ($path[0] != ".")
	  {
	    passthru("./test examples/" . $path, $result);
	    if ($result !== 0)
	      {
		echo "Test NOK\n";
	      }
	    else
	      {
		echo "Test OK\n";
	      }
	  }
      }
  }
