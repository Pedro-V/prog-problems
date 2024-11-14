import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.*;

class AdHoc {
  public static void main(String[] args) throws FileNotFoundException {
    Scanner sc = new Scanner(new FileInputStream("./sample1.input"));
    int tc = sc.nextInt();
    for (int i = 1; i <= tc; i++) {
      int[] xs = new int[3];
      for (int j = 0; j < xs.length; j++)
        xs[j] = sc.nextInt();
      Arrays.sort(xs);

      System.out.printf("Case %d: %d\n", i, xs[1]);

    }
    sc.close();
  }
}
