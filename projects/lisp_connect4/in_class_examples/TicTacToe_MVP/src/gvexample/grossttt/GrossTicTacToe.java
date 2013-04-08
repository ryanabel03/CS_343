package gvexample.grossttt;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

/**
 * This is an example of how *not* to write a GUI app.
 * Writing this code made me feel like I need to take a shower.
 *
 * @author Zachary Kurmas
 */
// Created  3/18/13 at 1:08 PM
// (C) Zachary Kurmas 2013

public class GrossTicTacToe implements ActionListener {

   private final JButton[][] board;
   private final JButton quitButton;
   private final JButton resetButton;
   private final JFrame frame;

   int currentPlayer = 0;

   /**
    * Throws an exception if the resource can't be found (as opposed to simply generating a blank icon)
    *
    * @param name the name of the resource
    * @return the {@code ImageIcon}
    */
   private static ImageIcon loadIcon(String name) {
      java.net.URL imgURL = GrossTicTacToe.class.getResource(name);
      if (imgURL == null) {
         throw new RuntimeException("Icon resource not found.");
      }
      return new ImageIcon(imgURL);
   }

   private static final ImageIcon xIcon = loadIcon("x.jpg");
   private static final ImageIcon oIcon = loadIcon("o.jpg");
   private static final ImageIcon emptyIcon = loadIcon("empty.jpg");

   /**
    * Constructor
    *
    * @param num_rows    the number of rows
    * @param num_columns the number of columns
    */
   public GrossTicTacToe(int num_rows, int num_columns) {

      //
      // Quit button and bottom panel
      //
      quitButton = new JButton("Quit");
      JPanel bottomPanel = new JPanel();
      bottomPanel.setLayout(new FlowLayout());
      bottomPanel.add(quitButton);
      quitButton.addActionListener(this);

      //
      // Reset button and bottom panel
      //
      resetButton = new JButton("Reset");
      bottomPanel.add(resetButton);
      resetButton.addActionListener(this);


      //
      // Board and main Panel
      //
      board = new JButton[num_rows][num_columns];
      JPanel squares = new JPanel();
      squares.setLayout(new GridLayout(num_rows, num_columns));
      for (int r = 0; r < num_rows; r++) {
         for (int c = 0; c < num_columns; c++) {
            board[r][c] = new JButton("", emptyIcon);
            squares.add(board[r][c]);
            board[r][c].addActionListener(this);
         }
      }

      //
      //  Frame
      //
      frame = new JFrame("Super Tic Tac Toe");
      JPanel mainPanel = new JPanel();
      mainPanel.setLayout(new BorderLayout());
      mainPanel.add(squares, BorderLayout.CENTER);
      mainPanel.add(bottomPanel, BorderLayout.SOUTH);
      frame.setContentPane(mainPanel);
      frame.pack();
      frame.setVisible(true);
      frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
   }


   public void displayResult(Icon status) {
      if (status == emptyIcon) {
         JOptionPane.showMessageDialog(frame, "We have a tie!", "Game Over", JOptionPane.PLAIN_MESSAGE);
      } else {
         JOptionPane.showMessageDialog(frame, "Congratulations, Player " + (status == xIcon ? "X" : "O"),
               "We have a winner!",
               JOptionPane.PLAIN_MESSAGE, status);
      }
      reset();
   }


   public void reset() {
      for (int r = 0; r < board.length; r++) {
         for (int c = 0; c < board[0].length; c++) {
            board[r][c].setIcon(emptyIcon);
         }
      }
      frame.repaint();
      currentPlayer = 0;
   }

   public void actionPerformed(ActionEvent actionEvent) {

      Object source = actionEvent.getSource();
      if (source == quitButton) {
         System.exit(0);
      } else if (source == resetButton) {
         reset();
      } else {
         for (int r = 0; r < board.length; r++) {
            for (int c = 0; c < board[r].length; c++) {
               if (source == board[r][c]) {
                  if (board[r][c].getIcon() == emptyIcon) {
                     board[r][c].setIcon(currentPlayer % 2 == 0 ? xIcon : oIcon);
                     currentPlayer++;
                     checkForWin();
                  }
               }
            }
         }
      }

   }

   private void checkForWin() {
      boolean winner;

      // check Rows
      for (int r = 0; r < board.length; r++) {
         winner = true;
         for (int c = 1; c < board[r].length; c++) {
            if (board[r][c].getIcon() != board[r][0].getIcon()) {
               winner = false;
            }
         }
         if (winner) {
            displayResult(board[r][0].getIcon());
         }
      }

      // check Column
      for (int c = 0; c < board[0].length; c++) {
         winner = true;
         for (int r = 0; r < board.length; r++) {
            if (board[r][c].getIcon() != board[0][c].getIcon()) {
               winner = false;
            }
         }
         if (winner) {
            displayResult(board[0][c].getIcon());
         }
      }

      // check forward diagonal
      winner = true;
      for (int r = 1; r < board.length; r++) {
         if (board[r][r].getIcon() != board[0][0].getIcon()) {
            winner = false;
         }
      }
      if (winner) {
         displayResult(board[0][0].getIcon());
      }

      // check backward diagonal
      winner = true;
      for (int r = 1; r < board.length; r++) {
         if (board[r][r].getIcon() != board[0][board.length - r - 0].getIcon()) {
            winner = false;
         }
      }
      if (winner) {
         displayResult(board[0][board.length - 1].getIcon());
      }
   }

   public static void main(String[] args) {
      new GrossTicTacToe(3,3);
   }
}

