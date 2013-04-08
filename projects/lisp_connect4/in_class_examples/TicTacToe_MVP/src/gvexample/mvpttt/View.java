package gvexample.mvpttt;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionListener;

/**
 * @author Zachary Kurmas
 */
// Created  3/18/13 at 11:50 AM
// (C) Zachary Kurmas 2013

public class View {

   private final JButton[][] board;
   private final JButton quitButton;
   private final JButton resetButton;
   private final JFrame frame;

   /**
    * Throws an exception if the resource can't be found (as opposed to simply generating a blank icon)
    *
    * @param name the name of the resource
    * @return the {@code ImageIcon}
    */
   private static ImageIcon loadIcon(String name) {
      java.net.URL imgURL = View.class.getResource(name);
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
   public View(int num_rows, int num_columns) {

      //
      // Quit button and bottom panel
      //
      quitButton = new JButton("Quit");
      JPanel bottomPanel = new JPanel();
      bottomPanel.setLayout(new FlowLayout());
      bottomPanel.add(quitButton);

      //
      // Reset button and bottom panel
      //
      resetButton = new JButton("Reset");
      bottomPanel.add(resetButton);


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


   /**
    * Place a new X or O in the board
    *
    * @param row    the row
    * @param column the column
    * @param state  the new state for the cell
    */
   public void update(int row, int column, CellState state) {
      board[row][column].setIcon(state == CellState.X ? xIcon : oIcon);
      frame.pack();
      frame.repaint();
   }


   public void addQuitListener(ActionListener actionListener) {
      quitButton.addActionListener(actionListener);
   }

   public void addCellListener(int r, int c, ActionListener actionListener) {
      board[r][c].addActionListener(actionListener);
   }

   public void displayResult(GameStatus status) {
      if (status == GameStatus.CATS) {
         JOptionPane.showMessageDialog(frame, "We have a tie!", "Game Over", JOptionPane.PLAIN_MESSAGE);
      } else {
         JOptionPane.showMessageDialog(frame, "Congratulations, Player " + status.toString(), "We have a winner!",
               JOptionPane.PLAIN_MESSAGE,
               status == GameStatus.X_WON ? xIcon : oIcon);
      }
   }

   public void addResetListener(ActionListener actionListener) {
      resetButton.addActionListener(actionListener);
   }

   public void reset(int num_rows, int num_columns) {
      for (int r = 0; r < num_rows; r++) {
         for (int c = 0; c < num_columns; c++) {
            board[r][c].setIcon(emptyIcon);
         }
      }
      frame.repaint();
   }
}
