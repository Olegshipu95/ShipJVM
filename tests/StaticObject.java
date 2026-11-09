public class StaticObject{

    int var1;
    int var2;

    public static StaticObject staticObject = new StaticObject(1,2);
    public static String my_string = "alloha";
    StaticObject (int a, int b) {
        var1 = a;
        var2 = b;
    }

    public static void main(String[] args) {
        StaticObject staticObject = new StaticObject(1,2);
        int c = staticObject.var1 + staticObject.var2;
    }

}
