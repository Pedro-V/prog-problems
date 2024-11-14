import java.util.Scanner;

public class AdHoc {

    public static void main(String[] args) {
        String[] keys = {
            "", "abc", "def",
            "ghi", "jkl", "mno",
            "pqrs", "tuv", "wxyz",
            "", " ", "",
        };
        Scanner sc = new Scanner(System.in);
        int tc = Integer.parseInt(sc.nextLine());
        for (int i = 1; i <= tc; i++) {
            int numPressings = 0;
            var msg = sc.nextLine().split("");
            for (var c : msg)
                for (var keySet : keys)
                    if (keySet.contains(c)) {
                        numPressings += keySet.indexOf(c) + 1;
                        break;
                    }

            System.out.printf("Case #%d: %d\n", i, numPressings);
        }
        sc.close();
    }
}