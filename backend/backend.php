



<?php

if(isset($_POST['move'])){
  $move = htmlspecialchars($_POST['move']);
  echo  json_encode(shell_exec('../logic/a.exe '.$move));
}




#echo json_encode();

>
