<?php
// common.php for graoom in /home/rannou_s/Work/graoom/test
// 
// Made by Sebastien Rannou
// Login   <rannou_s@epitech.net>
// 
// Started on  Sat Sep  5 14:47:54 2009 Sebastien Rannou
// Last update Sat Sep  5 15:17:48 2009 Sebastien Rannou
//

/**!
 * Someone cool would say it's better to get them though termcaps
 * Unfortunately, I'm NOT cool.
 */

define('COLOR_END'     		, "\033[00m");
define('COLOR_RED'     		, "\033[01;31m");
define('COLOR_GREEN'   		, "\033[01;32m");
define('COLOR_YELLOW'  		, "\033[01;33m");
define('COLOR_BLUE'    		, "\033[01;34m");

/**!
 * @author	rannou_s
 * Some common functions for tests
 */

function	ok()
{
  echo COLOR_GREEN . "\t\tOk" . COLOR_END .  "\n";
}

function	nok()
{
  echo COLOR_RED . "\t\tNok" . COLOR_END .  "\n";
}
