
import React from 'react';
import './ChessBoard.css';
import axios from 'axios';
var backLoc= "http://localhost:8000/backend/backend.php";
function GetPiece(c){

  if(c == 'P'){
    return '\u265F';
  }
  else if (c=='p') {
    return '\u2659';
  }
  else if (c=='R') {
    return '\u265C';
  }
  else if(c=='r'){
    return '\u2656';
  }
  else if(c == 'K'){
    return '\u265A';
  }
  else if (c == 'k') {
    return '\u2654';
  }
  else if(c == 'N'){
    return '\u265E';
  }
  else if(c == 'n'){
    return '\u2658';
  }
  else if (c=='Q'){
    return '\u265B';
  }
  else if(c == 'q'){
      return '\u2655';
  }
  else if (c == 'B') {
    return '\u265D';
  }
  else if(c =='b'){
    return '\u2657';
  }
  else{
    return "";
  }
}

class Square extends React.Component{
  constructor(props){
    super(props);
    this.state ={
      x : this.props.x,
      y : this.props.y,
      piece:this.props.piece

    };

    if(this.state.x%2==this.state.y%2){
      this.state.color = "black";
    }
    else{
      this.state.color = "white";
    }

  }

  render(){
    return(
      <button className = {this.state.color} onClick={this.props.func.bind(this,this.state.x,this.state.y)}  >{this.props.piece}</button>
    );
  }

}
class MovesList extends React.Component{
  constructor(props){
    super(props);

    this.state={
        moves :this.props.moves
    };
    this.state.ls = this.state.moves.map((move) =><li>{move}</li>);
  }

  render(){
   return (<ol>{this.state.ls}</ol>);
  }


}
class Board extends React.Component{
  constructor(props){
    super(props);
    this.state={
      x : -1,
      y : -1,
      src :  "new",
      xs : -1,
      ys:-1,
      xd:-1,
      yd:-1,
      pieces:"RNBQKBNRPPPPPPPPXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXpppppppprnbqkbnr",
      moves:[]
    };

    this.setMove = this.setMove.bind(this);
    this.SendMove = this.SendMove.bind(this);

  }




  SendMove(i,j){
    var m = this.state.src + " " + this.state.xs + " " + this.state.ys +" "+i+" "+j;

    if (i != -1 && j != -1){
      var form = new FormData();
      form.append("move",m);
      const response = axios.post(backLoc, form, {
        headers: { 'Content-Type': 'multipart/form-data' },})
        .then((response) => {
          console.log(response);

          this.setState({pieces:response['data']['board'],moves:m,src : "cache", xs : -1,ys:-1,xd:-1,yd:-1});

          //console.log(this.state);
        }, (error) => {
          console.log(error);
        });


        //console.log(this.state);
    }

  }

  setMove(i,j){
    this.setState({x:i,y:j});
    //var m = this.state.src + " (" + this.state.xs + "," + this.state.ys +","+this.state.xd+","+this.state.yd+")";
    //console.log(m);
    if(this.state.xs == -1 && this.state.ys == -1){
      this.setState({xs:i,ys:j});
    }
    else if(this.state.xd == -1 && this.state.yd == -1){
      //this.setState({xd:i,yd:j});
      this.SendMove(i,j);
      //console.log(this.state);
    }


  }
  renderSquare(i,j){
    return (<th key={i}><Square x={i} y={j} func = {this.setMove} piece={GetPiece(this.state.pieces.charAt(i+j*8))}/></th>);
  }
  renderRow(i){
    return [0,1,2,3,4,5,6,7].map( (n)=> this.renderSquare(n,i) );
  }
  renderBoard(){
    var L = new Array([]);
    var i;

    for(i=0;i<8;i++){
      L[i] = [<tr key={i}>{this.renderRow(i)}</tr>] ;

    }

    return L;
  }

  render(){
    console.log(this.state);
    return(

    <div >

    <div>  <h2>Current Move: ({this.state.xs}, {this.state.ys})=>({this.state.xd}, {this.state.yd}))</h2></div>


      <div className = "chessboard"><table  ><tbody>{this.renderBoard()}</tbody></table></div>
      <MovesList moves={this.state.moves}/>

    </div>
    );
  }
}
export default  Board;
