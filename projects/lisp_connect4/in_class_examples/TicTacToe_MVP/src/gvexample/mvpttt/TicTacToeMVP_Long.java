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

public class TicTacToeMVP_Long {

   private Model game;
   private View view;

   class ButtonListener implements ActionListener {
      private int row, column;

      ButtonListener(int row, int column) {
         this.row = row;
         this.column = column;
      }

      public void actionPerformed(ActionEvent actionEvent) {
         game.select(row, column);
         view.update(row, column, game.cellStatus(row, column));

         if (game.status() != GameStatus.IN_PROGRESS) {
            view.displayResult(game.status());
         }
      } // end actionPerformed
   } // end ButtonListener

   public TicTacToeMVP_Long(Model game_in, View view_in) {

      this.game = game_in;
      this.view = view_in;


      view.addQuitListener(new ActionListener() {
         public void actionPerformed(ActionEvent actionEvent) {
            System.exit(0);
         }
      });

      view.addResetListener(new ActionListener() {
         public void actionPerformed(ActionEvent actionEvent) {
            game.reset();
            view.reset(game.numRows(), game.numColumns());
         }
      });

      for (int r = 0; r < game.numRows(); r++) {
         for (int c = 0; c < game.numColumns(); c++) {
            view.addCellListener(r, c, new ButtonListener(r, c));
         }
      }
   }


   public static void main(String[] args) {
      int num_rows = 3;
      int num_columns = 3;
      Model game = new Model(num_rows, num_columns);
      View view = new View(num_rows, num_columns);
      new TicTacToeMVP(game, view);
   }

}
