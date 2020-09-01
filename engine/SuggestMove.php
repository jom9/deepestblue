<?php
 header("Access-Control-Allow-Origin: *");

if(isset($_POST['player']) and isset($_POST['depth']) and isset($_POST['board'])){
  $player = htmlspecialchars($_POST['player']);
  $depth = htmlspecialchars($_POST['depth']);
  $board = htmlspecialchars($_POST['board']);
  //
  $response->move = shell_exec('./a.out '.$player.' '.$depth.' '.$board);
   //$response->move = shell_exec('./a.out w 5 RNBQKBNRPPPPPPPPXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXpppppppprnbqkbnr');
   //$response->move = './a.out '.$player.' '.$depth.' '.$board;
  
}
else{
  $response->move = "False";
}
echo json_encode($response);

?>
