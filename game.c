#include "chess_base.h"
void move_piece(struct game * game, struct piece * piece, int x, int y){
  game->board[piece->y][piece->x] = 0;
  game->board[y][x] = piece;
  piece->x = x;
  piece->y = y;

}
char piece_symbol(struct piece * piece){
  if(!piece)
    return ' ';
  return (piece->side ? "pbnrqk":"PBNRQK")[piece->type];
}
void print_piece(struct piece * piece){
  printf("%c", piece_symbol(piece));
}
void print_board(struct game * game){
  for(int y = 7; y >= 0; y--){
    printf("%d ", y + 1);
    for(int x = 0; x < 8; x++){
      char * background = (((x + 1) % 2 && (y + 1) % 2) || (x % 2 && y % 2)) ? B_GREEN : B_WHITE;
      printf("\033[30m%s %c " "\033[0m", background, piece_symbol(game->board[y][x]));
    }
    printf("\n");
  }
  printf("   A  B  C  D  E  F  G  H\n");
}
void generate_pieces(struct side * side){
  int i = 0;
  for(int i = 0; i < 16; i++){
    side->pieces[i] = malloc(sizeof(struct piece));
    side->pieces[i]->captured = 0;
    side->pieces[i]->side = side->side;
  }
  for(int i = 0; i < 8; i++){
    side->pieces[i]->type = Pawn;
    side->pieces[i]->y = side->side ? 6 : 1;
    side->pieces[i]->x = i;
  }
  int start = side->side ? 7 : 0;
  int y = start;
  int inc = !side->side ? 1 : -1;
  PIECE_TYPE types[] = {Rook, Knight, Bishop, Queen, King, Bishop, Knight, Rook};
  for(int i = 8; i < 16; i ++){
    side->pieces[i]->type = types[start];
    side->pieces[i]->y = y;
    side->pieces[i]->x = i - 8;
    start += inc;
  }
}
struct game * generate_game(){
  struct game *game = malloc(sizeof(struct game));
  for(int side = 0; side < 2; side++){
    game->sides[side] = malloc(sizeof(struct side));
    game->sides[side]->side = side;
    generate_pieces(game->sides[side]);
  }
  for(int y = 0; y < 8; y++){
    for(int x = 0; x < 8; x++){
      game->board[y][x] = 0;
    }
  }
  for(int side = 0; side < 2; side ++){
    for(int i = 0; i < 16; i ++){
      struct piece * piece = game->sides[side]->pieces[i];
      game->board[piece->y][piece->x] = piece;
      game->pieces[side * 16 + i] = piece;
    }
  }
  return game;
}
/*
int main(){
  struct game * game = generate_game();
  game->board[2][2] = game->board[3][4] = malloc(sizeof(struct game));
  game->board[2][2]->side = game->board[3][4]->side = Black;
  print_board(game);
  for(int i = 0; i < 32; i++){
    struct piece * piece = game->pieces[i];
    print_piece(piece);
    printf(" (%d, %d) { ", piece->x, piece->y);
    for(int y = 0; y < 8; y ++)
      for(int x = 0; x < 8; x++)
	if(is_valid_move(game, piece, x, y))
	   printf("(%d, %d) ", x, y);
    printf("}\n");
  }
  return 0;
}
*/
