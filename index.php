<?php
$ip = $_SERVER['REMOTE_ADDR'];
$timestamp = time();
// $fileName = __DIR__."/logs/$timestamp.json";
$fileName = __DIR__."/logs.json";

$body = array("ip" => $ip, "time" => $timestamp, "data" => array());
$data = array();

foreach ($_REQUEST as $key => $value)
  $data[$key] = $value;

$body["data"] = $data;

$json_data = json_decode(file_get_contents(__DIR__."/logs.json"), true);
array_unshift($json_data, $body);

$fp = fopen($fileName, 'w');
fwrite($fp, json_encode($json_data));
fclose($fp);
?>
Hello <?=$ip?>, It's <?=$timestamp?>