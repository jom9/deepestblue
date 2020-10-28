import React from 'react';
import './ChessBoard.css';
class Square extends React.Component{
  constructor(props){
    super(props);
    this.state ={
      x : this.props.x,
      y : this.props.y,
      piece:this.props.piece

    };

    if(this.state.x%2===this.state.y%2){
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

export default Square;
