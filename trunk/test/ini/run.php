#!/usr/local/bin/php
<?php
// run.php for graoom in /home/rannou_s/Work/graoom/test/lists
// 
// Made by Sebastien Rannou
// Login   <rannou_s@epitech.net>
// 
// Started on  Fri Jul  3 22:53:08 2009 Sebastien Rannou
// Last update Fri Jul  3 23:27:22 2009 Sebastien Rannou
//

define(TMP_FILE, "/tmp/graoom_test");

passthru("locate php.ini > " . TMP_FILE);

if (($handle = fopen(TMP_FILE, "r")))
  {
    while (($path = fgets($handle)))
      {
	passthru("./ini " . trim($path), $result);
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
else
  {
    echo "Unable to fopen " . TMP_FILE . "\n";
  }
