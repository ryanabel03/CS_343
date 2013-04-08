package gvexample.mvpttt;

/**
 * @author Zachary Kurmas
 */
// Created  3/18/13 at 11:54 AM
// (C) Zachary Kurmas 2013

public class Model {

   private CellState[][] board;
   private CellState currentPlayer = CellState.X;
   private int numPlays = 0;

   public Model(int num_rows, int num_cols) {
      board = new CellState[num_rows][num_cols];
      reset();
   }

   public void select(int row, int column) throws RuntimeException {
      CellState item = board[row][column];

      if (item == CellState.EMPTY) {
         board[row][column] = currentPlayer;
         currentPlayer = (currentPlayer == CellState.X) ? CellState.O : CellState.X;
         numPlays++;
      } else {
         throw new RuntimeException("You can't do that!");
      }
   }

   public GameStatus status() {

      CellState state = checkForWin(board);
      if (state == CellState.X) {
         return GameStatus.X_WON;
      } else if (state == CellState.O) {
         return GameStatus.O_WON;
      } else if (state == null && numPlays != numRows() * numColumns()) {
         return GameStatus.IN_PROGRESS;
      } else if (state == null && numPlays == numRows() * numColumns()) {
         return GameStatus.CATS;
      } else {
         throw new RuntimeException("Programmer error.  This should never happen. " + state + " -- " + numPlays);
      }
   }

   public void reset() {
      numPlays = 0;
      currentPlayer = CellState.X;
      for (int r = 0; r < board.length; r++) {
         for (int c = 0; c < board[0].length; c++) {
            board[r][c] = CellState.EMPTY;
         }
      }
   }

   public int numRows() {
      return board.length;
   }

   public int numColumns() {
      return board[0].length;
   }

   public CellState cellStatus(int row, int column) {
      return board[row][column];
   }

   private interface MatrixAccessor {
      CellState get(int x);

      int length();
   }


   private static CellState findStreak(MatrixAccessor accessor) {
      for (int i = 1; i < accessor.length(); i++) {
          if (accessor.get(0) != accessor.get(i)) {
             return CellState.EMPTY;
          }
      }
      return accessor.get(0);
   }


   static CellState checkForWin(final CellState[][] board) {
      // Check each row for a win
      for (int r = 0; r < board.length; r++) {
         final int this_row = r;

         CellState row_result = findStreak(new MatrixAccessor() {
            public CellState get(int x) {
               return board[this_row][x % length()];
            }

            public int length() {
               return board[this_row].length;
            }
         });
         if (row_result != CellState.EMPTY) {
            return row_result;
         }
      } // end foreach row

      for (int c = 0; c < board[0].length; c++) {
         final int this_column = c;
         CellState column_result = findStreak(new MatrixAccessor() {
            public CellState get(int x) {
               return board[x % length()][this_column];
            }

            public int length() {
               return board.length;
            }
         });
         if (column_result != CellState.EMPTY) {
            return column_result;
         }
      } // end foreach column

      CellState forward = findStreak(new MatrixAccessor() {
         public CellState get(int x) {
            return board[x][x];
         }

         public int length() {
            return board.length;
         }
      });
      if (forward != CellState.EMPTY) {
         return forward;
      }

      CellState backward = findStreak(new MatrixAccessor() {
         public CellState get(int x) {
            return board[x][board[0].length - x -1];
         }

         public int length() {
            return board.length;
         }
      });
      if (backward != CellState.EMPTY) {
         return backward;
      }


      return null;
   }

}
