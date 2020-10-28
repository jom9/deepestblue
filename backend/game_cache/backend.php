



<?php
 header("Access-Control-Allow-Origin: *");
$response  = new \stdClass();
if(isset($_POST['move'])){
  $move = htmlspecialchars($_POST['move']);

  $response->board = shell_exec('backend.exe '.$move);

}
else{
  $response->board = "False";
}
echo json_encode($response);


?>
