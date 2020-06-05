import React from 'react';
import './ChessBoard.css';
class MovesList extends React.Component{

  constructor(props){
    super(props);

    this.state={
        moves :[]
    };

  }
  render(){
   return (
     <ol  className = "movelist" >{[...Array(this.props.moves.length).keys()].map((move) =><li className ="move" key={move} >{this.props.moves[move]}</li>)}</ol>
   );
  }


}
export default MovesList;
