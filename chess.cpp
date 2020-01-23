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

Square::Square(){}
Square::Square(int f,int r){
		file = f;
		rank = r;
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
			if(this->inside(this->file-1,this->rank+1)){ //checks upper left
				if(this->color != board[file-1][rank+1].piece.color){
					this->legalMoves.push_front( make_tuple( file-1,rank+1));
				}
			}
			if(this->inside(this->file,this->rank+1)) { // checks fwd
				if(this->color != board[file][rank+1].piece.color){
					this->legalMoves.push_front( make_tuple( file,rank+1));
				}
			}
			if(this->inside(this->file+1,this->rank+1)) { // checks upper righ
				if(this->color != board[file+1][rank+1].piece.color){
					this->legalMoves.push_front( make_tuple( file+1,rank+1));
				}
			}
			if(this->inside(this->file-1,this->rank)) { //checks left
				if(this->color != board[file-1][rank].piece.color){
					this->legalMoves.push_front( make_tuple( file-1,rank));
				}
			}
			if(this->inside(this->file+1,this->rank)) {// checks right
				if(this->color != board[file-1][rank].piece.color){
					this->legalMoves.push_front( make_tuple( file+1,rank));
				}
			}
			if(this->inside(this->file-1,this->rank-1)) {//back left
				if(this->color != board[file-1][rank-1].piece.color){
					this->legalMoves.push_front( make_tuple( file-1,rank-1));
				}
			}
			 if(this->inside(this->file,this->rank-1)) { // back
				if(this->color != board[file][rank-1].piece.color){
					this->legalMoves.push_front( make_tuple( file,rank-1));
				}
			}
			if(this->inside(this->file+1,this->rank-1)) { //back right
				if(this->color != board[file+1][rank-1].piece.color){
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
													}
													board[0][0].piece = Rook('w',0,0);// sets rooks
													board[7][0].piece = Rook('w',7,0);
													board[0][7].piece = Rook('b',0,7);
													board[7][7].piece = Rook('b',7,7);

													board[1][0].piece = Knight('w',1,0);// sets rooks
													board[6][0].piece = Knight('w',6,0);
													board[1][7].piece = Knight('b',1,7);
													board[6][7].piece = Knight('b',6,7);

													board[2][0].piece =  Bishop('w',2,0);// sets bishop
													board[5][0].piece = Bishop('w',5,0);
													board[2][7].piece = Bishop('b',2,7);
													board[5][7].piece = Bishop('b',5,7);

													board[3][0].piece =  Queen('w',3,0);// sets major piece
													board[4][0].piece = King('w',4,0);
													board[3][7].piece = Queen('b',3,7);
													board[4][7].piece = King('b',4,7);
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

void Board::updateBoard(){
		for(int i = 0; i<8; i++){
			for(int j =0 ; j<8; j++){
						board[i][j].piece.updateLegalMoves(board);
					}
			}
		}

void Board::takeMove(int xs,int ys,int xd,int yd){
	if(board[xs][ys].piece.rep == 'X'){
						cout<< "No piece here\n";
						return;
																		}
		else if(currentPlayer == 'w'){
			if(board[xs][ys].piece.color == 'b'){
				cout<<"Not your piece\n";
																					}
			else{
				bool isLegal = false;
																						//for (std::list<int>::iterator it=mylist.begin(); it != mylist.end(); ++it)
			for(list<tuple <int,int>>::iterator it=board[xs][ys].piece.legalMoves.begin(); it != board[xs][ys].piece.legalMoves.end(); ++it){
				cout<< get<0>(*it) << get<1>(*it)<<xd<<  yd<<'\t';
					if(get<0>(*it) == xd && get<1>(*it) == yd ){

							isLegal = true;
							break;
																							}
																						}
																				cout<<'\n';
						if(isLegal){
							if(board[xs][ys].piece.rep == 'P' && board[xs][ys].piece.enpass){
								if(xd == xs - 1 && yd ==ys+1){
									board[xs-1][ys].piece = Piece();

									board[xs-1][ys].piece.updatePos(xs-1,ys);
									board[xs][ys].piece.enpass = false;

								}
								else if(xd == xs +1 && yd ==ys+1){
									board[xs+1][ys].piece = Piece();

									board[xs+1][ys].piece.updatePos(xs-1,ys);
									board[xs][ys].piece.enpass = false;

								}
							}

							board[xd][yd].piece =	board[xs][ys].piece ;

							board[xs][ys].piece =  Piece();
							board[xs][ys].piece.updatePos(xs,ys);
							board[xd][yd].piece.updatePos(xd,yd);
							}
						else{
								cout<<"Not Legal\n";
																						}
																					}
								currentPlayer = 'b';
																				}
						else{
								if(board[xs][ys].piece.color == 'w'){
									cout<<"Not your piece\n";
																					}
								else{

									bool isLegal = false;
																											//for (std::list<int>::iterator it=mylist.begin(); it != mylist.end(); ++it)
								for(list<tuple <int,int>>::iterator it=board[xs][ys].piece.legalMoves.begin(); it != board[xs][ys].piece.legalMoves.end(); ++it){
									cout<< get<0>(*it) << get<1>(*it)<<xd<<  yd<<'\t';
										if(get<0>(*it) == xd && get<1>(*it) == yd ){
												isLegal = true;
												break;
																												}
																											}
																												cout<<'\n';
											if(isLegal){
												if(board[xs][ys].piece.rep == 'P' && board[xs][ys].piece.enpass){
													if(xd == xs - 1 && yd ==ys+1){
														board[xs-1][ys].piece = Piece();

														board[xs-1][ys].piece.updatePos(xs-1,ys);
														board[xs][ys].piece.enpass = false;

													}
													else if(xd == xs +1 && yd ==ys+1){
														board[xs+1][ys].piece = Piece();

														board[xs+1][ys].piece.updatePos(xs-1,ys);
														board[xs][ys].piece.enpass = false;

													}
												}
												board[xd][yd].piece =	board[xs][ys].piece ;
												board[xs][ys].piece =  Piece();
												board[xs][ys].piece.updatePos(xs,ys);
												board[xd][yd].piece.updatePos(xd,yd);
												}
											else{
													cout<<"Not Legal\n";
																											}
												}
									currentPlayer = 'w';
									turnNum++;

																				}
											updateBoard();

	}


	int main(){

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


		return 0;
	}
