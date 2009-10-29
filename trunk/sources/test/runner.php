#!/usr/local/bin/php
<?php
// runner.php for battletrantor in /home/rannou_s/Work/graoom/test
// 
// Made by Sebastien Rannou
// Login   <rannou_s@epitech.net>
// 
// Started on  Sat Sep  5 14:57:37 2009 Sebastien Rannou
// Last update Sun Jul 19 14:35:02 2009 sebastien rannou
//

/**!
 * @author	rannou_s
 * Would probably be better in shell...
 */

$dir = opendir(".");

if (!file_exists("../bin/battletrantor-server/"))
  die("Unable to find server's binary\n");

if (!$dir)
  die("Ugh@?!?\n");

while (($item = readdir($dir)))
  {
    if (is_dir($item))
      {
	if (file_exists($item . "/run.php"))
	  {
	    chdir($item);
	    passthru("php run.php");
	    chdir("..");
	  }
      }
  }

closedir($dir);
