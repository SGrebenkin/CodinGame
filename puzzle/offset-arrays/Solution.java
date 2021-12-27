//https://www.codingame.com/ide/puzzle/offset-arrays
import java.util.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import java.io.*;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
class Solution {

    static Pattern requestPattern = Pattern.compile("^([A-Z]+)\\[(.*)\\]$");
    public static int getNumber(String x, HashMap<String, ArrayList<Integer>> mp, HashMap<String, Integer> mn) throws IOException {
        if (x.matches("-?\\d+"))
            return Integer.parseInt(x);
        Matcher m = requestPattern.matcher(x);
        if (!m.find())
            throw new IOException();

        String arrayName = m.group(1);
        return mp.get(arrayName).get(getNumber(m.group(2), mp, mn) - mn.get(arrayName));
    }

    public static void main(String args[]) throws IOException {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        if (in.hasNextLine())
            in.nextLine();
        HashMap<String, ArrayList<Integer>> mp = new HashMap<>();
        HashMap<String, Integer> mn = new HashMap<>();

        Pattern pattern = Pattern.compile("(^.*)\\[(.*)[.][.](.*)\\]\\s*=\\s*(.*)");
        for (int i = 0; i < n; i++) {
            String assignment = in.nextLine();
            Matcher m = pattern.matcher(assignment);
            if (!m.find())
                continue;

            String arrayName = m.group(1);
            mn.put(arrayName, Integer.parseInt(m.group(2)));

            String nums[] = m.group(4).split(" ");
            ArrayList<Integer> al = new ArrayList<>();
            for (int j = 0; j < nums.length; ++j)
                al.add(Integer.parseInt(nums[j]));
            mp.put(arrayName, al);
        }

        String x = in.nextLine();
        System.out.println(getNumber(x, mp, mn));
    }
}