<?php
// moulinette.php for zappy in /home/rannou_s/zappy1/srcs/server
// 
// Made by sebastien rannou
// Login   <rannou_sepitech.net>
// 
// Started on  Mon Apr 27 15:48:59 2009 sebastien rannou
//

error_reporting(0); // No need?!

if (!($argc == 3))
  {
    color_red_start();
    echo "usage: php moulinette.php [ip] [port]\n";
    color_end();
    die();
  }

$ip = $argv[1];
$port = $argv[2];

$sockets = array();	// array of sockets, used for several tests
$test_id = 1;		// current id of the running test

define('FIXTURE', "Ne laisse jamais la haine obscurcir la raison premiere de ton coeur. !@#$%^&*()_+}{[]:;><.,?");

function	get_answer($sock)
{
  return fgets($sock);
}

function	test_connect()
{
  global	$ip;
  global	$port;

  if (($tmp = fsockopen($ip, $port)))
    {
      fclose($tmp);
      return TRUE;
    }
  return FALSE;
}

if (!test_connect())
  {
    color_red_start();
    echo "Unable to connect to server\n";
    color_end();
    die();
  }

function	color_green_start()
{
  echo "\033[01;32m";
}

function	color_red_start()
{
  echo "\033[01;31m";
}

function	color_end()
{
  echo "\033[00m";
}

function	launch_test($string, $level)
{
  global	$test_id;

  color_green_start();
  echo "Test number " . $test_id . " difficulty: " . $level . "/5\n";
  color_end();
  echo "\t" . $string . "\n";
  $test_id++;
}

function	end_test()
{
  global	$test_id;  

  sleep(5);
  if (!test_connect())
    {
      color_red_start();
      echo "Test failed (" . $test_id . ") fucking bastard\n";
      color_end();
      die();
    }
  color_green_start();
  echo "Test completed\n\n";
  color_end();
}

function	clean_sockets()
{
  global	$sockets;

  foreach ($sockets as $sock)
    fclose($sock);
}

function	create_connect()
{
  global	$ip;
  global	$port;

  return fsockopen($ip, $port);
}

// Test 1
launch_test("Memory test", 3);
$sock = create_connect();
$str = "";
for ($j = 0; $j < 16; $j++)
  $str .= FIXTURE;
for ($i = 0; $i < 1024; $i++)
  {
    $j = fwrite($sock, $str);
    if ($j === 0 || $j === false)
      break;
  }
fclose($sock);
end_test();

// Test 6
launch_test("Network test (can be long)", 2);
for ($i = 0; $i < 4096; $i++)
  {
    $sock = create_connect();
    fclose($sock);
  }
end_test();

// Test 7
launch_test("CPU test (can be long)", 5);
for ($i = 0; $i < 2048; $i++)
  {
    $sockets[] = create_connect();
  }
clean_sockets();
end_test();

//Yaw!
color_green_start();
echo "Hey, it seems to be working\n\n";
color_end();
echo "Don't forget to add your own tests and to share them!\n";

?>
