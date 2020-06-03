<?php
 header("Access-Control-Allow-Origin: *");

if(isset($_POST['player']) and isset($_POST['depth']) and isset($_POST['board'])){
  $player = htmlspecialchars($_POST['player']);
  $depth = htmlspecialchars($_POST['depth']);
  $board = htmlspecialchars($_POST['board']);
  $response = shell_exec('./a.out '.$player.' '.$depth.' '.$board);

}
else{
  $response->board = "False";
}
echo json_encode($response);



#echo json_encode(); php -S localhost:8000

?>
