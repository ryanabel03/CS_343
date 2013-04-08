/**
 * @author Zachary Kurmas
 */
// Created  3/22/13 at 12:30 PM
// (C) Zachary Kurmas 2013

public class FTicTacToe {

   public static Integer[] intList(int n) {
      Integer[] answer = new Integer[n];
      for (int i = 0; i < n; i++) {
         answer[i] = i;
      }
      return answer;
   }


   public static <T> T[] getColumn(T[][] matrix, final int colnum) {
      return FMap.map(matrix, matrix[0][0].getClass(), new FMap.MapFunction<T[], T>() {
         public T map(T[] in) {
            return in[colnum];
         }
      });
   }

   public static <T> T[][] allColumns(final T[][] matrix) {
      return FMap.map(intList(matrix.length), matrix[0].getClass(),
            new FMap.MapFunction<Integer, T[]>() {
               public T[] map(Integer in) {
                  return getColumn(matrix, in);
               }
            });
   }

   public static int firstPositive(Integer[] values) {
      for (Integer val : values) {
         if (val > 0) {
            return val;
         }
      }
      return -1;
   }

   public static int allSame(Integer[] values) {
      for (int i = 1; i < values.length; i++) {
         if (!values[i].equals(values[0])) {
            return -1;
         }
      }
      return values[0];
   }

   public static int tttWin_simple(final Integer[][] matrix) {
      return firstPositive(FMap.map(allColumns(matrix), Integer.class, new FMap.MapFunction<Integer[], Integer>() {
         public Integer map(Integer[] in) {
            return allSame(in);
         }
      }));
   }

   public static int tttWin(final Integer[][] matrix) {
      return firstPositive(FMap.map(append(matrix, allColumns(matrix)),
            Integer.class, new FMap.MapFunction<Integer[], Integer>() {
         public Integer map(Integer[] in) {
            return allSame(in);
         }
      }));
   }

   public static Integer[][] append(Integer[][]... input) {
      int totalLength = 0;
      for (Integer[][] matrix : input) {
         totalLength += matrix.length;
      }
      Integer[][] output = new Integer[totalLength][];
      int i = 0;
      for (Integer[][] matrix : input) {
         for (Integer[] row : matrix) {
            output[i++] = row;
         }
      }
      return output;
   }


   public static int tttWin_broken(final Integer[][] matrix) {

      FMap.MapFunction<Integer[][], Integer[][]> colsf =
            new FMap.MapFunction<Integer[][], Integer[][]>() {
               public Integer[][] map(Integer[][] in) {
                  return allColumns(in);
               }
            };

      FMap.MapFunction<Integer[][], Integer[][]> rowsf =
            new FMap.MapFunction<Integer[][], Integer[][]>() {
               public Integer[][] map(Integer[][] in) {
                  return in;
               }
            };

      // Fails here:  Can't have array of generics.
      // Solution:  Re-write map to use a List.
      //FMap.MapFunction<Integer[][], Integer[][]>[] = {colsf, rowsf}

      Object[] fns = {colsf, rowsf};

      Integer[][][] views = FMap.map(fns, matrix.getClass(), new FMap.MapFunction<Object, Integer[][]>() {
         public Integer[][] map(Object in) {
            return ((FMap.MapFunction<Integer[][], Integer[][]>) in).map(matrix);
         }
      });

      return firstPositive(FMap.map(append(views), Integer.class, new FMap.MapFunction<Integer[], Integer>() {
         public Integer map(Integer[] in) {
            return allSame(in);
         }
      }));
   }


   public static void main(String[] args) {
      Integer[][][] matrices = {
            {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}},
            {{1, 2, 3, 4}, {5, 2, 7, 8}, {9, 2, 11, 12}, {13, 2, 15, 16}},
            {{1, 2, 3, 4}, {5, 6, 7, 8}, {10, 10, 10, 10}, {13, 14, 15, 16}}
      };

      int i = 1;
      for (Integer[][] matrix : matrices)
         System.out.printf("Winner of matrix %d is %d\n", i++, tttWin(matrix));
   }
}
