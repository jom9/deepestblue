#include <iostream>


#include "chess.h"

using namespace std;

char opColor(char c){ //method that inverts the colors
	if(c=='w'){
		return 'b';
	}
	else if(c=='b'){
		return 'w';
	}
	else{
		return c;
	}
}
Piece::Piece(){rep = 'X';}
Piece::Piece(char c,int f,int r){
			file = f;
			rank = r;
			color =c;

		}
bool Piece::inside(int x, int y){// is the piece inside the board

			if(x>7 || x<0){ return false;}
			if(y>7 || y<0){ return false;}
			return true;
		}
void Piece::updatePos(int f,int r){
	file = f;
	rank = r;
}
void Piece::updateLegalMoves(Square board[8][8]){
	switch(rep){
		case 'P':{

			Pawn P = Pawn(color,file,rank);
			P.updateLegalMoves(board);
			legalMoves = P.legalMoves;
			break;
		}
		case 'N':{

			Knight P = Knight(color,file,rank);
			P.updateLegalMoves(board);
			legalMoves = P.legalMoves;
			break;
		}
		case 'Q':{

			Queen P = Queen(color,file,rank);
			P.updateLegalMoves(board);
			legalMoves = P.legalMoves;
			break;
		}
		case 'K':{

			King P = King(color,file,rank);
			P.updateLegalMoves(board);
			legalMoves = P.legalMoves;
			break;
		}
		case 'R':{

			Rook P = Rook(color,file,rank);
			P.updateLegalMoves(board);
			legalMoves = P.legalMoves;
			break;
		}
		case 'B':{

			Bishop P = Bishop(color,file,rank);
			P.updateLegalMoves(board);
			legalMoves = P.legalMoves;
			break;
		}
		default:{

		}
	}
}// possible moves, empty for parent class, tuples
void Piece::updateAttacks(Square board[8][8]){
	switch(rep){
		case 'P':{

			Pawn P = Pawn(color,file,rank);
			P.updateAttacks(board);
			attacks = P.attacks;
			break;
		}
		case 'N':{

			Knight P = Knight(color,file,rank);
			P.updateLegalMoves(board);
			attacks = P.legalMoves;
			break;
		}
		case 'Q':{

			Queen P = Queen(color,file,rank);
			P.updateLegalMoves(board);
			attacks = P.legalMoves;
			break;
		}
		case 'K':{

			King P = King(color,file,rank);
			P.updateLegalMoves(board);
			attacks = P.legalMoves;
			break;
		}
		case 'R':{

			Rook P = Rook(color,file,rank);
			P.updateLegalMoves(board);
			attacks = P.legalMoves;
			break;
		}
		case 'B':{

			Bishop P = Bishop(color,file,rank);
			P.updateLegalMoves(board);
			attacks = P.legalMoves;
			break;
		}
		default:{

		}
	}

}
Square::Square(){attackedByWhite=0; // number of pieces attaking this square
attackedByBlack=0 ;}
Square::Square(int f,int r){
		file = f;
		rank = r;
		attackedByWhite=0; // number of pieces attaking this square
		attackedByBlack =0;
	}
void Square::setPos(int f,int r){ // sets position of square
		file = f;
		rank = r;
	}
tuple <int,int> Square::getPos(){ // returns values of square
			return make_tuple(file,rank);
		}

King::King(char c,int x,int y):Piece(c,x,y){rep = 'K'; generic = false;	}
void King::updateLegalMoves(Square board[8][8]){
			this->legalMoves.clear();
			if(color == 'w'){
			if(this->inside(this->file-1,this->rank+1) && this->color != board[file-1][rank+1].piece.color && board[file-1][rank+1].attackedByBlack==0){ //checks upper left
					this->legalMoves.push_front( make_tuple( file-1,rank+1));
			}
			if(this->inside(this->file,this->rank+1)&& this->color != board[file][rank+1].piece.color && board[file][rank+1].attackedByBlack==0) { // checks fwd
					this->legalMoves.push_front( make_tuple( file,rank+1));

			}
			if(this->inside(this->file+1,this->rank+1)&&this->color != board[file+1][rank+1].piece.color && board[file+1][rank+1].attackedByBlack==0) { // checks upper right
					this->legalMoves.push_front( make_tuple( file+1,rank+1));
			}
			if(this->inside(this->file-1,this->rank)&&this->color != board[file-1][rank].piece.color && board[file-1][rank].attackedByBlack==0) { //checks left
					this->legalMoves.push_front( make_tuple( file-1,rank));
			}
			if(this->inside(this->file+1,this->rank)&&this->color != board[file+1][rank].piece.color && board[file+1][rank].attackedByBlack==0) {// checks right
					this->legalMoves.push_front( make_tuple( file+1,rank));
			}
			if(this->inside(this->file-1,this->rank-1)&&this->color != board[file-1][rank-1].piece.color && board[file-1][rank-1].attackedByBlack==0) {//back left
					this->legalMoves.push_front( make_tuple( file-1,rank-1));
			}
			 if(this->inside(this->file,this->rank-1)&&this->color != board[file][rank-1].piece.color && board[file][rank-1].attackedByBlack==0) { // back
					this->legalMoves.push_front( make_tuple( file,rank-1));
			}
			if(this->inside(this->file+1,this->rank-1)&&this->color != board[file+1][rank-1].piece.color && board[file+1][rank-1].attackedByBlack==0) { //back right
					this->legalMoves.push_front( make_tuple( file+1,rank-1));
			}

		}
		if(color == 'b'){
		if(this->inside(this->file-1,this->rank+1) && this->color != board[file-1][rank+1].piece.color && board[file-1][rank+1].attackedByWhite==0){ //checks upper left
				this->legalMoves.push_front( make_tuple( file-1,rank+1));
		}
		if(this->inside(this->file,this->rank+1)&& this->color != board[file][rank+1].piece.color&& board[file][rank+1].attackedByWhite==0) { // checks fwd
				this->legalMoves.push_front( make_tuple( file,rank+1));
		}
		if(this->inside(this->file+1,this->rank+1)&&this->color != board[file+1][rank+1].piece.color&& board[file+1][rank+1].attackedByWhite==0) { // checks upper right
				this->legalMoves.push_front( make_tuple( file+1,rank+1));
		}
		if(this->inside(this->file-1,this->rank)&&this->color != board[file-1][rank].piece.color&& board[file-1][rank].attackedByWhite==0) { //checks left
				this->legalMoves.push_front( make_tuple( file-1,rank));
		}
		if(this->inside(this->file+1,this->rank)&&this->color != board[file+1][rank].piece.color&& board[file+1][rank].attackedByWhite==0) {// checks right
				this->legalMoves.push_front( make_tuple( file+1,rank));
		}
		if(this->inside(this->file-1,this->rank-1)&&this->color != board[file-1][rank-1].piece.color&& board[file-1][rank-1].attackedByWhite==0) {//back left
				this->legalMoves.push_front( make_tuple( file-1,rank-1));
		}
		 if(this->inside(this->file,this->rank-1)&&this->color != board[file][rank-1].piece.color&& board[file][rank-1].attackedByWhite==0) { // back
				this->legalMoves.push_front( make_tuple( file,rank-1));
		}
		if(this->inside(this->file+1,this->rank-1)&&this->color != board[file+1][rank-1].piece.color&& board[file+1][rank-1].attackedByWhite==0) { //back right
				this->legalMoves.push_front( make_tuple( file+1,rank-1));
		}

	}
	}
Knight::Knight(char c,int x,int y):Piece(c,x,y){rep = 'N'; generic = false;	}
void Knight::updateLegalMoves(Square board[8][8]){
			this->legalMoves.clear();
			if(this->inside(file+1,rank+2)){
				if(this->color!=board[file+1][rank+2].piece.color){
					this->legalMoves.push_front(make_tuple(file+1,rank+2));
				}
			}
			if(this->inside(file+2,rank+1)){
				if(this->color!=board[file+2][rank+1].piece.color){
					this->legalMoves.push_front(make_tuple(file+2,rank+1));
				}
			}
			if(this->inside(file+2,rank-1)){
				if(this->color!=board[file+2][rank-1].piece.color){
					this->legalMoves.push_front(make_tuple(file+2,rank-1));
				}
			}
			if(this->inside(file+1,rank-2)){
				if(this->color!=board[file+1][rank-2].piece.color){
					this->legalMoves.push_front(make_tuple(file+1,rank-2));
				}
			}
			if(this->inside(file-1,rank-2)){
				if(this->color!=board[file-1][rank-2].piece.color){
					this->legalMoves.push_front(make_tuple(file-1,rank-2));
				}
			}
			if(this->inside(file-2,rank-1)){
				if(this->color!=board[file-2][rank-1].piece.color){
					this->legalMoves.push_front(make_tuple(file-2,rank-1));
				}
			}
			if(this->inside(file-2,rank+1)){
				if(this->color!=board[file-2][rank+1].piece.color){
					this->legalMoves.push_front(make_tuple(file-2,rank+1));
				}
			}
			if(this->inside(file-1,rank+2)){
				if(this->color!=board[file-1][rank+2].piece.color){
					this->legalMoves.push_front(make_tuple(file-1,rank+2));
				}
			}
		}
Pawn::Pawn(char c,int x,int y):Piece(c,x,y){rep ='P'; generic = false;	}
void Pawn::updateAttacks(Square board[8][8]){
				if(color == 'w'){
						if(inside(file-1,rank+1)){
							this->attacks.push_front(make_tuple(file-1,rank+1));
						}
						if(inside(file+1,rank+1)){
							this->attacks.push_front(make_tuple(file+1,rank+1));
						}
				}
				else if(color =='b'){
					if(inside(file-1,rank-1)){
						this->attacks.push_front(make_tuple(file-1,rank-1));
					}
					if(inside(file+1,rank-1)){
							this->attacks.push_front(make_tuple(file+1,rank-1));
					}
				}
			}
void Pawn::updateLegalMoves( Square board[8][8]){
			if(color == 'w'){

				this->legalMoves.clear();
					if(firstmove){
						if(this->inside(file,rank+2)){
							if( board[file][rank+2].piece.rep == 'X'){
								this->legalMoves.push_front(make_tuple(file,rank+2));

								this->firstmove = false;
							}
						}
					}


					if(this->inside(file-1,rank+1)){
						if(board[file-1][rank+1].piece.color== opColor(this->color )){
							this->legalMoves.push_front(make_tuple(file-1,rank+1));

							this->firstmove = false;
						}
						if( board[file-1][rank].piece.color== opColor(this->color ) && board[file-1][rank].piece.rep == 'P' && board[file-1][rank].piece.firstmove){//en passant
							this->legalMoves.push_front(make_tuple(file-1,rank+1));
							board[file-1][rank].piece.enpass =true;
							enpass =true;
						}
					}
					if(this->inside(file,rank+1)){
						if( board[file][rank+1].piece.rep == 'X'){
							this->legalMoves.push_front(make_tuple(file,rank+1));

							this->firstmove = false;
						}
					}
					if(this->inside(file+1,rank+1)){
						if(board[file+1][rank+1].piece.color && opColor(this->color )){
							this->legalMoves.push_front(make_tuple(file+1,rank+1));
							this->firstmove = false;

						}
						if(board[file+1][rank].piece.color== opColor(this->color ) && board[file+1][rank].piece.rep == 'P' && board[file+1][rank].piece.firstmove){//en passant
							this->legalMoves.push_front(make_tuple(file+1,rank+1));
							board[file+1][rank].piece.enpass =true;
							enpass =true;
						}
					}

				}
				else if(color == 'b'){
					this->legalMoves.clear();
						if(firstmove){
							if(this->inside(file,rank-2)){
								if(board[file][rank-2].piece.rep =='X'){
									this->legalMoves.push_front(make_tuple(file,rank-2));

									this->firstmove = false;
								}
							}
						}

						if(this->inside(file-1,rank-1)){
							if(board[file-1][rank-1].piece.color== opColor(this->color )){
								this->legalMoves.push_front(make_tuple(file-1,rank-1));

								this->firstmove = false;
							}
							if(board[file-1][rank].piece.color== opColor(this->color )&& board[file-1][rank].piece.rep == 'P' && board[file-1][rank].piece.firstmove ){//en passant
								this->legalMoves.push_front(make_tuple(file-1,rank-1));
								board[file-1][rank].piece.enpass =true;
								enpass =true;
							}
						}
						if(this->inside(file,rank-1)){
							if(board[file][rank-1].piece.rep == 'X'){
								this->legalMoves.push_front(make_tuple(file,rank-1));

								this->firstmove = false;
							}
						}
						if(this->inside(file+1,rank-1)){
							if(board[file+1][rank-1].piece.color== opColor(this->color )){
								this->legalMoves.push_front(make_tuple(file+1,rank-1));
								this->firstmove = false;

							}
							if( board[file+1][rank].piece.color== opColor(this->color )&& board[file+1][rank].piece.rep == 'P' && board[file+1][rank].piece.firstmove ){//en passant
								this->legalMoves.push_front(make_tuple(file+1,rank-1));
								board[file+1][rank].piece.enpass =true;
								enpass =true;
							}
						}
				}
				}
Rook::Rook(char c,int x,int y):Piece(c,x,y){rep ='R';	 generic = false;}
void Rook::updateLegalMoves(Square board[8][8]){
							this->legalMoves.clear();
							int i=1; // next fur while loops iterater through
							while(this->inside(this->file + i, this->rank)){
								if(this->color != board[file+i][rank].piece.color ){
									if(this->color == opColor(board[file+i][rank].piece.color)){
											this->legalMoves.push_front(make_tuple(file+i,rank));
											break;
									}else{
										this->legalMoves.push_front(make_tuple(file+i,rank));
									}
								}
								else{
									break;
								}


								i++;
							}
							i=1;
							while(this->inside(this->file - i, this->rank)){
								if(this->color != board[file-i][rank].piece.color ){
									if(this->color == opColor(board[file-i][rank].piece.color)){
											this->legalMoves.push_front(make_tuple(file-i,rank));
											break;
									}else{
										this->legalMoves.push_front(make_tuple(file-i,rank));
									}
								}
								else{
									break;
								}

								i++;
							}
							i=1;
							while(this->inside(this->file , this->rank+i)){
								if(this->color != board[file][rank+i].piece.color ){
									if(this->color == opColor(board[file][rank+i].piece.color)){
											this->legalMoves.push_front(make_tuple(file,rank+i));
											break;
									}else{
										this->legalMoves.push_front(make_tuple(file,rank+i));
									}
								}
								else{
									break;
								}


								i++;
							}
							i=1;
							while(this->inside(this->file , this->rank-i)){
								if(this->color != board[file][rank-i].piece.color ){
									if(this->color == opColor(board[file][rank+i].piece.color)){
											this->legalMoves.push_front(make_tuple(file,rank-i));
											break;
									}else{
										this->legalMoves.push_front(make_tuple(file,rank-i));
									}
								}
								else{
									break;
								}


								i++;
							}


						}
Bishop::Bishop(char c,int x,int y):Piece(c,x,y){rep ='B';	 generic = false;}
void Bishop::updateLegalMoves(Square board[8][8]){
									this->legalMoves.clear();
									int i=1;
									while(this->inside(this->file + i, this->rank+i)){
										if(this->color != board[file+i][rank+i].piece.color ){
											if(this->color == opColor(board[file+i][rank+i].piece.color)){
													this->legalMoves.push_front(make_tuple(file+i,rank+i));
													break;
											}else{
												this->legalMoves.push_front(make_tuple(file+i,rank+i));
											}
										}
										else{
											break;
										}


										i++;
									}
									i=1;
									while(this->inside(this->file - i, this->rank-i)){
										if(this->color != board[file-i][rank-i].piece.color ){
											if(this->color == opColor(board[file-i][rank-i].piece.color)){
													this->legalMoves.push_front(make_tuple(file-i,rank-i));
													break;
											}else{
												this->legalMoves.push_front(make_tuple(file-i,rank-i));
											}
										}
										else{
											break;
										}

										i++;
									}
									i=1;
									while(this->inside(this->file-i , this->rank+i)){
										if(this->color != board[file-i][rank+i].piece.color ){
											if(this->color == opColor(board[file-i][rank+i].piece.color)){
													this->legalMoves.push_front(make_tuple(file-i,rank+i));
													break;
											}else{
												this->legalMoves.push_front(make_tuple(file-i,rank+i));
											}
										}
										else{
											break;
										}


										i++;
									}
									i=1;
									while(this->inside(this->file+i , this->rank-i)){
										if(this->color != board[file+i][rank-i].piece.color ){
											if(this->color == opColor(board[file+i][rank-i].piece.color)){
													this->legalMoves.push_front(make_tuple(file+i,rank-i));
													break;
											}else{
												this->legalMoves.push_front(make_tuple(file+i,rank-i));
											}
										}
										else{
											break;
										}


										i++;
									}


								}
Queen::Queen(char c,int x,int y):Piece(c,x,y){rep ='Q'; generic = false;	}
void Queen::updateLegalMoves(Square board[8][8]){
											this->legalMoves.clear();
											int i=1;
											while(this->inside(this->file + i, this->rank)){
												if(this->color != board[file+i][rank].piece.color ){
													if(this->color == opColor(board[file+i][rank].piece.color)){
															this->legalMoves.push_front(make_tuple(file+i,rank));
															break;
													}else{
														this->legalMoves.push_front(make_tuple(file+i,rank));
													}
												}
												else{
													break;
												}
												i++;
											}
											i=1;
											while(this->inside(this->file - i, this->rank)){
												if(this->color != board[file-i][rank].piece.color ){
													if(this->color == opColor(board[file-i][rank].piece.color)){
															this->legalMoves.push_front(make_tuple(file-i,rank));
															break;
													}else{
														this->legalMoves.push_front(make_tuple(file-i,rank));
													}
												}
												else{
													break;
												}

												i++;
											}
											i=1;
											while(this->inside(this->file , this->rank+i)){
												if(this->color != board[file][rank+i].piece.color ){
													if(this->color == opColor(board[file][rank+i].piece.color)){
															this->legalMoves.push_front(make_tuple(file,rank+i));
															break;
													}else{
														this->legalMoves.push_front(make_tuple(file,rank+i));
													}
												}
												else{
													break;
												}


												i++;
											}
											i=1;
											while(this->inside(this->file , this->rank-i)){
												if(this->color != board[file][rank-i].piece.color ){
													if(this->color == opColor(board[file][rank+i].piece.color)){
															this->legalMoves.push_front(make_tuple(file,rank-i));
															break;
													}else{
														this->legalMoves.push_front(make_tuple(file,rank-i));
													}
												}
												else{
													break;
												}


												i++;
											}

											i=1;
											while(this->inside(this->file + i, this->rank+i)){
												if(this->color != board[file+i][rank+i].piece.color ){
													if(this->color == opColor(board[file+i][rank+i].piece.color)){
															this->legalMoves.push_front(make_tuple(file+i,rank+i));
															break;
													}else{
														this->legalMoves.push_front(make_tuple(file+i,rank+i));
													}
												}
												else{
													break;
												}


												i++;
											}
											i=1;
											while(this->inside(this->file - i, this->rank-i)){
												if(this->color != board[file-i][rank-i].piece.color ){
													if(this->color == opColor(board[file-i][rank-i].piece.color)){
															this->legalMoves.push_front(make_tuple(file-i,rank-i));
															break;
													}else{
														this->legalMoves.push_front(make_tuple(file-i,rank-i));
													}
												}
												else{
													break;
												}

												i++;
											}
											i=1;
											while(this->inside(this->file-i , this->rank+i)){
												if(this->color != board[file-i][rank+i].piece.color ){
													if(this->color == opColor(board[file-i][rank+i].piece.color)){
															this->legalMoves.push_front(make_tuple(file-i,rank+i));
															break;
													}else{
														this->legalMoves.push_front(make_tuple(file-i,rank+i));
													}
												}
												else{
													break;
												}


												i++;
											}
											i=1;
											while(this->inside(this->file+i , this->rank-i)){
												if(this->color != board[file+i][rank-i].piece.color ){
													if(this->color == opColor(board[file+i][rank-i].piece.color)){
															this->legalMoves.push_front(make_tuple(file+i,rank-i));
															break;
													}else{
														this->legalMoves.push_front(make_tuple(file+i,rank-i));
													}
												}
												else{
													break;
												}


												i++;
											}


										}
Board::Board(){// board constructor
													for(int i=0;i<8;i++){
														for(int j=0;j<8;j++){
															board[i][j].setPos(i,j); // inits board, sets square coors
															board[i][j].piece.updatePos(i,j);
															if(j%2 == 0){
																if(i%2 == 0){
																	board[i][j].color = 'b';
																}
																else{
																	board[i][j].color = 'w';
																}
															}
															else{
																if(i%2 == 0){
																	board[i][j].color = 'w';
																}
																else{
																	board[i][j].color = 'b';
																}
															}
														}

													}

													for(int i=0;i<8;i++){
														board[i][1].piece = Pawn('w',i,1);// sets white pawns
														board[i][6].piece = Pawn('b',i,6);// sets black pawns
														blackPos.push_front(make_tuple(i,6));// sets list of pawns
														whitePos.push_front(make_tuple(i,1));
													}
													board[0][0].piece = Rook('w',0,0);// sets rooks
													board[7][0].piece = Rook('w',7,0);
													board[0][7].piece = Rook('b',0,7);
													board[7][7].piece = Rook('b',7,7);
													blackPos.push_front(make_tuple(0,7));
													blackPos.push_front(make_tuple(7,7));
													whitePos.push_front(make_tuple(0,0));
													whitePos.push_front(make_tuple(7,0));

													board[1][0].piece = Knight('w',1,0);// sets rooks
													board[6][0].piece = Knight('w',6,0);
													board[1][7].piece = Knight('b',1,7);
													board[6][7].piece = Knight('b',6,7);
													blackPos.push_front(make_tuple(1,7));
													blackPos.push_front(make_tuple(6,7));
													whitePos.push_front(make_tuple(1,7));
													whitePos.push_front(make_tuple(6,7));

													board[2][0].piece =  Bishop('w',2,0);// sets bishop
													board[5][0].piece = Bishop('w',5,0);
													board[2][7].piece = Bishop('b',2,7);
													board[5][7].piece = Bishop('b',5,7);
													blackPos.push_front(make_tuple(2,7));
													blackPos.push_front(make_tuple(2,7));
													whitePos.push_front(make_tuple(2,0));
													whitePos.push_front(make_tuple(5,0));

													board[3][0].piece =  Queen('w',3,0);// sets major piece
													board[4][0].piece = King('w',4,0);
													board[3][7].piece = Queen('b',3,7);
													board[4][7].piece =  King('b',4,7);
													blackPos.push_front(make_tuple(3,7));
													blackPos.push_front(make_tuple(4,7));
													whitePos.push_front(make_tuple(3,0));
													whitePos.push_front(make_tuple(4,0));

													updateBoard();
													}
void Board::printBoard(){ //test function for debugging
	for(int j=7;j>=0;j--){
			for(int i=0;i<8;i++){
					if(board[i][j].piece.color == 'w'){
						cout<<"\033[0;31m" <<board[i][j].piece.rep<<"\033[0m" <<"\t";
		}
				else if (board[i][j].piece.color == 'b'){
						cout<<"\033[0;34m"<<board[i][j].piece.rep<<"\033[0m"<<"\t";
				}
				else{
					cout<<board[i][j].piece.rep<<"\t";
						}
														}
																			cout<<"\n";
																	}
																}
bool Board::updateBoard(){
	for(int i = 0; i<8; i++){
		for(int j =0 ; j<8; j++){
					board[i][j].attackedByBlack = 0; // resets the counter counting how many pieces can attack a square
					board[i][j].attackedByWhite = 0;
				}
		}

		for(int i = 0; i<8; i++){
			for(int j =0 ; j<8; j++){
						board[i][j].piece.updateLegalMoves(board);
						board[i][j].piece.updateAttacks(board);
						if(board[i][j].piece.color == 'w'){

						for(list<tuple <int,int>>::iterator it=board[i][j].piece.attacks.begin(); it != board[i][j].piece.attacks.end(); ++it){

						board[get<0>(*it)][get<1>(*it)].attackedByWhite+=1;
					}
					}
					if(board[i][j].piece.color == 'b'){
					for(list<tuple <int,int>>::iterator it=board[i][j].piece.attacks.begin(); it != board[i][j].piece.attacks.end(); ++it){
						board[get<0>(*it)][get<1>(*it)].attackedByBlack+=1;
				}
				}
			}
		}

			if(board[get<0>(wkingPos)][get<1>(wkingPos)].attackedByBlack){
				wchecked = true;
			}
			if(board[get<0>(bkingPos)][get<1>(bkingPos)].attackedByWhite ){
				bchecked = true;
			}
			currentPlayer = opColor(currentPlayer);
			if(currentPlayer=='w'){
			turnNum++;}
			return checkmate();
	}
bool Board::checkmate(){
	if(currentPlayer=='w'){
		if(wchecked){
				if(board[get<0>(wkingPos)][get<1>(bkingPos)].piece.legalMoves.empty()){
					return true;
				}
		}
	}else{
		if(bchecked){
				if(board[get<0>(bkingPos)][get<1>(bkingPos)].piece.legalMoves.empty()){
					return true;
				}
		}
	}

	return false;
}
bool Board::isLegal(int xs,int ys,int xd,int yd){
	if(!board[0][0].piece.inside(xs,ys) || !board[0][0].piece.inside(xd,yd)){// is the move within the limits of the board
		cout<<"Not inside";
		return false;
	}
	if(wchecked){// checks if white king is in check
		if(get<0>(wkingPos) != xs || get<1>(wkingPos) != ys ){
			cout << "In check" << '\n';
			return false;
		}
	}
	////////////////////
	if(bchecked){// checks if the black black king is in check
		if(get<0>(bkingPos) != xs || get<1>(bkingPos) != ys ){
			cout << "In check" << '\n';
			return false;
		}
	}
	//////////////////
	if(board[xs][ys].piece.rep == 'X'){//checks if theres piece on the square
						cout<< "No piece here\n";
						return false;
					}
	else if(currentPlayer == 'w'){ // its the white players turn
	if(board[xs][ys].piece.color == 'b'){// white can't move blacks pieces
							cout<<"Not your piece\n";
							return false;
						}
					}
		for(list<tuple <int,int>>::iterator it=board[xs][ys].piece.legalMoves.begin(); it != board[xs][ys].piece.legalMoves.end(); ++it){
			// iterates through each of the moves and checks if the inputted move is in the set of legal legalMoves
			if(get<0>(*it) == xd && get<1>(*it) == yd ){
				return true;
			}
		}


		///////////////////////////////now blacks conds
		if(currentPlayer== 'b'){
			if(board[xs][ys].piece.color == 'w'){// checks if the target is black
				cout<<"Not your piece\n";
				return false;
																}
		}
		for(list<tuple <int,int>>::iterator it=board[xs][ys].piece.legalMoves.begin(); it != board[xs][ys].piece.legalMoves.end(); ++it){
			//iterates throught possible moves
				if(get<0>(*it) == xd && get<1>(*it) == yd ){
					return true;
				}
			}



	return false;
}
tuple <int,int> Board::captures(int xs,int ys,int xd,int yd){
	if(board[xs][ys].piece.color=='w' && board[xd][yd].piece.color=='b'){
		return make_tuple(xd,yd);
	}
	else if(board[xs][ys].piece.color=='w' & board[xs][ys].piece.enpass){
			return make_tuple(xd,ys);;
	}
	if(board[xs][ys].piece.color=='b' && board[xd][yd].piece.color=='w'){
		return make_tuple(xd,yd);
	}
	else if(board[xs][ys].piece.color=='b' & board[xs][ys].piece.enpass){
		return make_tuple(xd,ys);
	}
	return make_tuple(-1,-1);
}
void Board::updateWhite(int xs,int ys,int xd,int yd){
		tuple <int,int> cap = captures(xs,ys,xd,yd); // checks if piece will be captured
		if(board[xs][ys].piece.rep == 'P' && board[xs][ys].piece.enpass){ //checks if its a pawn can perform enpassent

			if(xd == xs - 1 && yd ==ys+1){ //left capture
				board[xs-1][ys].piece = Piece();//removes the piece next to the attecking pawn
				board[xs-1][ys].piece.updatePos(xs-1,ys);// updatePos of square
				board[xs][ys].piece.enpass = false; // resets enpass boolean
			}
			else if(xd == xs +1 && yd ==ys+1){// right capture
				board[xs+1][ys].piece = Piece();// updates pos of square
				board[xs+1][ys].piece.updatePos(xs-1,ys);
				board[xs][ys].piece.enpass = false; //resets bool
			}
		}


			if( board[xs][ys].piece.rep == 'K'){// is the targeted piece a king?
				wkingPos = make_tuple(xd,yd); //updates king pos
				if(wchecked){ //checks i
					wchecked=false; // since this move is assumed to be legal, it must there be a move that gets the king out of check, so we can remove the check counter
				}
			}

			int i =0;
			for(list<tuple <int,int>>::iterator it=whitePos.begin(); it != whitePos.end(); ++it){
				//iterates throught possible moves
					if(get<0>(*it) == xs && get<1>(*it) == ys ){
						whitePos.erase(it);
						whitePos.push_front(make_tuple(xd,yd));
						break;
					}
					i++;
				}
			if(get<0>(cap)!=-1  && get<1>(cap)!=-1){
				i=0;
				for(list<tuple <int,int>>::iterator it=blackPos.begin(); it != blackPos.end(); ++it){
					//iterates throught possible moves
						if(get<0>(*it) == get<0>(cap) && get<1>(*it) == get<1>(cap) ){
							blackPos.erase(it);
							break;
						}
						i++;
					}

			}
			board[xd][yd].piece =	board[xs][ys].piece ; //moves piece to new squrare
			board[xs][ys].piece =  Piece(); // blanks source square
			board[xs][ys].piece.updatePos(xs,ys);  // update Pos
			board[xd][yd].piece.updatePos(xd,yd);  // update Pos


}
void Board::updateBlack(int xs,int ys,int xd,int yd){
	tuple<int,int> cap = captures(xs,ys,xd,yd); // checks if piece will be captured
	if(board[xs][ys].piece.rep == 'P' && board[xs][ys].piece.enpass){ //enpassent
		if(xd == xs - 1 && yd ==ys+1){ //left enpass capture
			board[xs-1][ys].piece = Piece();
			board[xs-1][ys].piece.updatePos(xs-1,ys);// makes sure the piece is removed from board
			board[xs][ys].piece.enpass = false;

		}

		else if(xd == xs +1 && yd ==ys+1){ // right enpass capture
			board[xs+1][ys].piece = Piece(); // makes sure the piece is removed from board
			board[xs+1][ys].piece.updatePos(xs-1,ys);
			board[xs][ys].piece.enpass = false;

		}

	}
	if( board[xs][ys].piece.rep == 'K'){
		bkingPos = make_tuple(xd,yd);
		if(bchecked){
			bchecked=false;
		}
	}
	int i =0;
	for(list<tuple <int,int>>::iterator it=blackPos.begin(); it != blackPos.end(); ++it){
		//iterates throught possible moves
			if(get<0>(*it) == xs && get<1>(*it) == ys ){
				blackPos.erase(it);
				blackPos.push_front(make_tuple(xd,yd));
				break;
			}
			i++;
		}
	if(get<0>(cap)!=-1  && get<1>(cap)!=-1){
		i=0;
		for(list<tuple <int,int>>::iterator it=whitePos.begin(); it != whitePos.end(); ++it){
			//iterates throught possible moves
				if(get<0>(*it) == get<0>(cap) && get<1>(*it) == get<1>(cap) ){
					whitePos.erase(it);
					break;
				}
				i++;
			}

	}
	board[xd][yd].piece =	board[xs][ys].piece ; //moves piece to new squrare
	board[xs][ys].piece =  Piece(); // blanks source square
	board[xs][ys].piece.updatePos(xs,ys);  // update Pos
	board[xd][yd].piece.updatePos(xd,yd);  // update Pos
}
bool Board::takeMove(int xs,int ys,int xd,int yd){ //function to make move source -> destination
	if(isLegal(xs,ys,xd,yd)){
		if(currentPlayer=='w'){
			updateWhite(xs,ys,xd,yd);
		}else{
			updateBlack(xs,ys,xd,yd);
		}

	}

										return	updateBoard();

	}
list <tuple<int,int,int,int>> Board::legalMoves(){
	list <tuple<int,int,int,int>> L;
	if(currentPlayer=='w'){
		for(list<tuple <int,int>>::iterator it1=whitePos.begin(); it1 != whitePos.end(); ++it1){
			Piece P = board[get<0>(*it1)][get<1>(*it1)].piece;
			for(list<tuple <int,int>>::iterator it2=P.legalMoves.begin(); it2 != P.legalMoves.end(); ++it2){
				L.push_front(	make_tuple(	get<0>(*it1),	get<1>(*it1),	 get<0>(*it2),	get<1>(*it2) ));
			}
		}
	}
	else{
		for(list<tuple <int,int>>::iterator it1=blackPos.begin(); it1 != blackPos.end(); ++it1){
			Piece P = board[get<0>(*it1)][get<1>(*it1)].piece;
			for(list<tuple <int,int>>::iterator it2=P.legalMoves.begin(); it2 != P.legalMoves.end(); ++it2){
				L.push_front(	make_tuple(	get<0>(*it1),	get<1>(*it1),	 get<0>(*it2),	get<1>(*it2) ));
			}
		}
	}

	return L;
}
bool Board::takeMove(int xs,int ys,int xd,int yd,bool isLegal){// same function as before but it assumes the move is legal
	if(currentPlayer=='w'){
		updateWhite(xs,ys,xd,yd);
	}else{
		updateBlack(xs,ys,xd,yd);
	}
	return	updateBoard();
}

/*
	int main(int argc, char *argv[]){
		if(argc== 2){
			Board b;
			b.printBoard();
			b.takeMove(4,1,4,3);
			b.printBoard();
			b.takeMove(4,6,4,4);
			b.printBoard();
			b.takeMove(4,0,4,1);
			b.printBoard();
			b.takeMove(5,6,5,4);
			b.printBoard();
			b.takeMove(4,1,5,2);
			b.printBoard();
			b.takeMove(5,4,4,3);
			b.printBoard();
			b.takeMove(5,2,5,3);
			b.printBoard();
		}
		else{


		Board b;
		b.printBoard();
		int xs,ys,xd,yd;
		while(true){
			cout<<"Enter Move\n";
			cin>>xs>>ys>>xd>>yd;
			if(xs == -1 && ys == -1 && xd == -1 && yd == -1){

				cout<<"Done!";
				break;
			}
			else{
				b.takeMove(xs,ys,xd,yd);
			}
			b.printBoard();
		}

	}
		return 0;
	}
*/
