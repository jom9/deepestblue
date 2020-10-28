
import React from 'react';
import { StyleSheet, Text, View } from 'react-native';
import './ChessBoard.css';
import Square from "./Square.js";
import MovesList from "./MovesList.js";
import SuggestMove from "./SuggestMove.js";
import $ from "jquery";
import axios from 'axios';
import backend_loc from "./globals.js";
var backLoc=backend_loc+"game_cache/backend.php";//"http://localhost:8000/game_cache/backend.php" //backend_loc+"game_cache/backend.php";
console.log(backLoc)
function GetPiece(c){

  if(c === 'P'){
    return '\u265F';
  }
  else if (c==='p') {
    return '\u2659';
  }
  else if (c==='R') {
    return '\u265C';
  }
  else if(c==='r'){
    return '\u2656';
  }
  else if(c === 'K'){
    return '\u265A';
  }
  else if (c === 'k') {
    return '\u2654';
  }
  else if(c === 'N'){
    return '\u265E';
  }
  else if(c === 'n'){
    return '\u2658';
  }
  else if (c==='Q'){
    return '\u265B';
  }
  else if(c === 'q'){
      return '\u2655';
  }
  else if (c === 'B') {
    return '\u265D';
  }
  else if(c === 'b'){
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
    var xspos = ((xs)*100+120);// 100 is length of cell
    var yspos = ((ys)*100+139);
    var xdpos = ((xd)*100+120);
    var ydpos = ((yd)*100+139);
    //const canvas = this.refs.canvas;
    //const ctx = canvas.getContext("2d");
    //canvas.width
    var length = Math.sqrt( (xspos-xdpos)*(xspos-xdpos)+(yspos-ydpos)*(yspos-ydpos) );

      var angle = Math.atan2( (yd-ys) , (xd - xs) )*(360/6.28) -45;


    const arrow = {
      head:{
        position:'absolute',
        borderColor: "#CBEEFF",
        borderTopWidth:0,
        borderRightWidth:10,
        borderBottomWidth:10,
        borderLeftWidth:0,
        padding: 10,
        display: 'inline-block',
        transform: 'rotate('+angle+'deg)',
        top:ydpos,
        left:xdpos
      },
      line:{
      position:'absolute',
      top:yspos+7,
      left:xspos+15,
      backgroundColor:"#CBEEFF",
      width:length,
      height:7,
      transformOrigin: '0% 50%',
      transform: 'rotate('+(angle+45)+'deg)',
      }
    };


    return <div style={{position:'absolute',top:0,left:0}}><View style={arrow.head}/><View style={arrow.line}/></div>

  }


  oppPlayer(c){
    if(c==='w'){
      return 'b';
    }
    else if(c==='b'){
      return 'w';
    }
  }
  SendMove(i,j){
    var m = this.state.src + " " + this.state.xs + " " + this.state.ys +" "+i+" "+j;

    if (i !== -1 && j !== -1){
      var form = new FormData();
      form.append("move",m);
      form.append("board",this.state.pieces);
      form.append("player",this.state.player);

      const response = axios.post(backLoc, form, {
        headers: { 'Content-Type': 'multipart/form-data' },})
        .then((response) => {
          console.log(response);


          if(!RegExp("InvalidMove").test(response['data']['board']) && response['data']['board']!= this.state.pieces ){
              var editedMoves = this.state.moves;
              var piece = GetPiece(  this.state.pieces.charAt(this.state.xs+this.state.ys*8)  )
              var move =  piece+ String.fromCharCode(65 + this.state.xs)+(this.state.ys+1)+"=>"+String.fromCharCode(65 + i)+(j+1);
              editedMoves.push(move);

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
    if(this.state.xs === -1 && this.state.ys === -1){
      this.setState({xs:i,ys:j});
    }
    else if(this.state.xd === -1 && this.state.yd === -1){
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
