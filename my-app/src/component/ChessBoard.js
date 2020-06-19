
import React from 'react';
import './ChessBoard.css';
import Square from "./Square.js";
import MovesList from "./MovesList.js";
import SuggestMove from "./SuggestMove.js";
import axios from 'axios';

var backLoc= "https://web.njit.edu/~jom9/deepestblue/backend/backend.php";
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
      moves:[],
      player:'w',
      xss:0,
      yss:0,
      xds:0,
      yds:0,

    };

    this.setMove = this.setMove.bind(this);
    this.SendMove = this.SendMove.bind(this);
    this.getSuggestMove = this.getSuggestMove.bind(this);
    this.setSuggestMove = this.setSuggestMove.bind(this);
  }
  setSuggestMove(xs,ys,xd,yd){
    this.setState({xss:xs,yss:ys,xds:xd,yds:yd});
  }
  getSuggestMove(){

    var xs = parseFloat(this.state.xss);
    var ys = parseFloat(this.state.yss);
    var xd = parseFloat(this.state.xds);
    var yd = parseFloat(this.state.yds);
    var xspos = ((xs)*100+120);
    var yspos = ((ys)*100+120);
    var xdpos = ((xd)*100+80);
    var ydpos = ((yd)*100+180);
    var length = (Math.sqrt((xspos-xdpos)*(xspos-xdpos)+(yspos-ydpos)*(yspos-ydpos))-40)+"px";
    var totalL = ((Math.sqrt((xspos-xdpos)*(xspos-xdpos)+(yspos-ydpos)*(yspos-ydpos)))-10)+"px";
    var xm= (xspos+xdpos)/2;
    var ym= (yspos+ydpos)/2;
  if(xs!=xd){
    var angle = "rotate("+  (Math.atan((yd-ys)/(xd-xs))*(360/6.28)+180)+"deg)";
  }
  else{
    if(ys>yd){
      var angle = "rotate(-90deg)";
    }else{
      var angle = "rotate(90deg)";
    }
  }
    var xpos= xm+"px";
    var ypos= ym+"px";

    console.log(xs,ys,xd,yd);
    console.log(length,xspos,yspos,angle);

    return (<div className="arrow" style={{transform:angle,top:ypos,left:xpos,width:totalL}}>
    <div className="line" style={{width:length}}></div>
    <div className="point" ></div>
    </div>);
    /*
    return (<div className="arrow" style={{transform:"rotate(45deg)"}}>
    <div className="line" ></div>
    <div className="point" ></div>
    </div>);*/
  }


  oppPlayer(c){
    if(c=='w'){
      return 'b';
    }
    else if(c=='b'){
      return 'w';
    }
  }
  SendMove(i,j){
    var m = this.state.src + " " + this.state.xs + " " + this.state.ys +" "+i+" "+j;

    if (i != -1 && j != -1){
      var form = new FormData();
      form.append("move",this.state.xs + " " + this.state.ys +" "+i+" "+j);
      form.append("board",this.state.pieces);
      form.append("player",this.state.player);
      const response = axios.post(backLoc, form, {
        headers: { 'Content-Type': 'multipart/form-data' },})
        .then((response) => {
          //console.log(response);


          if(!RegExp("InvalidMove").test(response['data']['board']) && response['data']['board']!= this.state.pieces ){
              var editedMoves = this.state.moves;
              var move = String.fromCharCode(65 + this.state.xs)+(this.state.ys+1)+"=>"+String.fromCharCode(65 + i)+(j+1);
              editedMoves.push(move);
              console.log(move);
              var next = {pieces:response['data']['board'],moves:editedMoves,src : "cache", xs : -1,ys:-1,xd:-1,yd:-1,player:this.oppPlayer(this.state.player)}
              if(this.state != next){
                this.setState({pieces:response['data']['board'],moves:editedMoves,src : "cache", xs : -1,ys:-1,xd:-1,yd:-1,player:this.oppPlayer(this.state.player)});
              }


          }else{
              this.setState({xs : -1,ys:-1,xd:-1,yd:-1});
          }



        }, (error) => {
          console.log(error);
        });


    }

  }

  setMove(i,j){
    this.setState({x:i,y:j});
    if(this.state.xs == -1 && this.state.ys == -1){
      this.setState({xs:i,ys:j});
    }
    else if(this.state.xd == -1 && this.state.yd == -1){
      this.SendMove(i,j);
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

      L[i] = [<tr key={i}><th style ={{color:"#DCDCDC"}}>{8-i}</th>{this.renderRow(i)}</tr>] ;

    }
    L[8]= <tr key='8'>{[' ','A','B','C','D','E','F','G','H'].map( (file) => <th style ={{color:"#DCDCDC"}} key={file}>{file}</th>)}</tr>;
    return L;
  }

  render(){
    return(

      <div style={{backgroundColor: "#282c34"}}>

      <div style={{backgroundColor: "#282c34"}}>
      <div className = "chessboard">{this.getSuggestMove()}<table ><tbody>{this.renderBoard()}</tbody></table></div>


      </div>
      <div style={{backgroundColor: "#282c34"}}>
      <MovesList moves={this.state.moves} ></MovesList>
      <SuggestMove player={this.state.player} board={this.state.pieces} func={this.setSuggestMove}/>
      </div>
      </div>


    );
  }
}
export default  Board;
