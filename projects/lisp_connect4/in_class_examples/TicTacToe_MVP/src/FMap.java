import java.lang.reflect.Array;
import java.util.Arrays;

/**
 * @author Zachary Kurmas
 */
// Created  3/22/13 at 12:12 PM
// (C) Zachary Kurmas 2013

public class FMap {

   public interface IntMapFunction {
      int map(int i);
   }

   public static int[] intMap(int[] input, IntMapFunction f) {
      int[] output = new int[input.length];
      for (int i = 0; i < input.length; i++) {
         output[i] = f.map(input[i]);
      }
      return output;
   }

   public interface MapFunction<I, O> {
      O map(I in);
   }

   public static <I, O> O[] map(I[] input, Class<?> outputType, MapFunction<I, O> f) {
      @SuppressWarnings("unchecked")
      O[] output = (O[]) Array.newInstance(outputType, input.length);
      for (int i = 0; i < input.length; i++) {
         output[i] = f.map(input[i]);
      }
      return output;
   }

   static class Student {
      public String name;
      public double gpa;
      public int credits;

      Student(String name, double gpa, int credits) {
         this.name = name;
         this.gpa = gpa;
         this.credits = credits;
      }
   }


   public static void main(String[] args) {
      Student[] students = {new Student("Bob", 3.821, 15),
            new Student("Mary", 3.994, 33),
            new Student("Nikki", 1.092, 13)};

      String[] names = map(students, String.class, new MapFunction<Student, String>() {
         public String map(Student in) {
            return in.name;
         }
      });
      System.out.println(Arrays.toString(names));

      Double[] gpas = map(students, Double.class, new MapFunction<Student, Double>() {
         public Double map(Student in) {
            return in.gpa;
         }
      });
        System.out.println(Arrays.toString(gpas));
   }


}
