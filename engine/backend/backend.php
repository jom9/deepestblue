



<?php
 header("Access-Control-Allow-Origin: *");// FOR DEV SERVER ONLY!!!!!!!!

if(isset($_POST['move'])){
  $move = htmlspecialchars($_POST['move']);

  $response->board = shell_exec('GetGameFromCache.exe '.$move);
  //$response->board = '"../logic/a.exe" '.$move;
  //$response->board = "Work PLZ";
  //echo shell_exec('"../logic/a.exe" new 4 6 4 4 ');
}
else{
  $response->board = "False";
}
echo json_encode($response);



#echo json_encode(); php -S localhost:8000

?>
