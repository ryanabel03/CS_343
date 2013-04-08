import java.lang.reflect.Array;

/**
 * Created with IntelliJ IDEA.
 * User: kurmasz
 * Date: 3/25/13
 * Time: 2:33 PM
 * To change this template use File | Settings | File Templates.
 */
public class FMap2 {

    public interface IntMapFunction {
        public int map(int i);
    }


    public static int[] intMap(int[] array, IntMapFunction f) {
        int[] output = new int[array.length];
        for (int i = 0; i < array.length; i++) {
            output[i] = f.map(array[i]);
        }
        return output;
    }

    public interface MapFunction<I, O> {
        public O map(I in);
    }


    public static <I, O> O[] map( I[] input, Class<O> output_type, MapFunction<I, O> f) {
        O[] output = (O[]) Array.newInstance(output_type, input.length);
        for (int i = 0; i < input.length; i++) {
            output[i] = f.map(input[i]);
        }
        return output;
    }

    public static void main(String[] args) {
        Integer[] input = {1, 2, 4, 6, 9, 11};
        Double[] output = map(input, Double.class, new MapFunction<Integer, Double>() {
            public Double map(Integer in) {
                return in / 2.0;
            }
        });
    }



}
