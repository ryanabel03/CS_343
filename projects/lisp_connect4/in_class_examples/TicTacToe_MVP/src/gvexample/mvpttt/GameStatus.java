package gvexample.mvpttt;

/**
 * Describes the status of a Super Tic Tac Toe game
 * @author Zachary Kurmas
 */
// Created  1/18/13 at 1:49 PM
// (C) Zachary Kurmas 2013

public enum GameStatus {


   X_WON("X"),

   O_WON("O"),

   /**
    * Tie game
    */
   CATS("Tie"), IN_PROGRESS("In progress");

   private String name;

   GameStatus(String name) {
      this.name = name;
   }

   public String toString() {
      return name;
   }
}
