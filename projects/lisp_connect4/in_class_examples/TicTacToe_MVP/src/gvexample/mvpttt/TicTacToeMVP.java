package gvexample.mvpttt;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

/**
 * The driver for a game of Super TicTacToe
 *
 * @author Zachary Kurmas
 */
// Created  1/18/13 at 4:30 PM
// (C) Zachary Kurmas 2013

public class TicTacToeMVP {

   Model game;
   View view;

   public TicTacToeMVP(final Model game, final View view) {

      this.game = game;
      this.view = view;


      view.addQuitListener(new ActionListener() {
         public void actionPerformed(ActionEvent actionEvent) {
            System.exit(0);
         }
      });

      view.addResetListener(new ActionListener() {
         public void actionPerformed(ActionEvent actionEvent) {
            reset();
         }
      });

      for (int r = 0; r < game.numRows(); r++) {
         for (int c = 0; c < game.numColumns(); c++) {
            final int this_row = r;
            final int this_column = c;
            view.addCellListener(r, c, new ActionListener() {
               public void actionPerformed(ActionEvent actionEvent) {
                  game.select(this_row, this_column);
                  view.update(this_row, this_column, game.cellStatus(this_row, this_column));

                  if (game.status() != GameStatus.IN_PROGRESS) {
                     view.displayResult(game.status());
                  }

               }
            });
         }
      }
   }

   private void reset() {
      game.reset();
      view.reset(game.numRows(), game.numColumns());
   }


   public static void main(String[] args) {
      int num_rows = 3;
      int num_columns = 3;
      Model game = new Model(num_rows, num_columns);
      View view = new View(num_rows, num_columns);
      new TicTacToeMVP(game, view);
   }

}
