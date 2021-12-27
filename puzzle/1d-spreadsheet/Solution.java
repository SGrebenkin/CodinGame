// https://www.codingame.com/ide/puzzle/1d-spreadsheet
import java.util.*;
import java.io.*;
import java.math.*;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
class Solution {

    public static class Task {
        public String operation;
        public String arg1;
        public String arg2;
        public int result;
        public Boolean calculated;

        public void set(int _r) {
            calculated = true;
            result = _r;
        }

        public Task(String _o, String _a1, String _a2) {
            operation = _o;
            arg1 = _a1;
            arg2 = _a2;
            calculated = false;
            result = 0;
        }
    }

    public static int calculate(List<Task> _t, int _i) {
        Task t = _t.get(_i);
        if (t.calculated)
            return t.result;

        if (t.operation.equals("VALUE")) {
            if (t.arg1.startsWith("$"))
                t.set(calculate(_t, Integer.parseInt(t.arg1.substring(1))));
            else
                t.set(Integer.parseInt(t.arg1));
        }
        else {
            int res1;
            String arg1 = t.arg1;
            if (arg1.startsWith("$"))
                res1 = calculate(_t, Integer.parseInt(arg1.substring(1)));
            else
                res1 = Integer.parseInt(arg1);

            int res2;
            String arg2 = t.arg2;
            if (arg2.startsWith("$"))
                res2 = calculate(_t, Integer.parseInt(arg2.substring(1)));
            else
                res2 = Integer.parseInt(arg2);

            int res = 0;
            if (t.operation.equals("ADD"))
                res = res1 + res2;
            else if (t.operation.equals("SUB"))
                res = res1 - res2;
            else if (t.operation.equals("MULT"))
                res = res1 * res2;

            t.set(res);
        }

        return t.result;
    }

    public static void main(String args[]) {
        Scanner in = new Scanner(System.in);
        int N = in.nextInt();

        List<Task> tasks = new ArrayList<>();
        for (int i = 0; i < N; ++i) {
            String operation = in.next();
            String arg1 = in.next();
            String arg2 = in.next();

            tasks.add(new Task(operation, arg1, arg2));
        }

        for (int i = 0; i < N; ++i)
            System.out.println(calculate(tasks, i));
    }
}
