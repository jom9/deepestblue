<?php
 header("Access-Control-Allow-Origin: *");// FOR DEV SERVER ONLY!!!!!!!!

 $myfile = fopen("info.html", "r") or die("Unable to open file!");
 echo fread($myfile,filesize("info.html"));
 fclose($myfile);
 ?>
