public class Add {
    static final int aboba = 100;

    public static int add2(int i, int b)
    {
        return i+ b + aboba;
    }

    public static int add(int i, int b)
    {
        return (add2(i,b));
    }

    public static void main(String[] args) {
        int i = -1;
        int i2 = 4;
		int i3 = add(i, i2);
        int i4 = i3 + i2 + i;
    }
}
