public class New extends New_Parent {

  static New New_object = new New(1,2);
  int i;
  int b;

  New(int i, int b)
  {
    this.i = i;
    this.b = b;
  }

  public int add()
  {
    return i + b;
  }

    public static void main(String[] args) {
      int a = 1;
      int b = 2;
      New test = new New(a,b);
      int c = test.add();
      int r = c + b + a;
    }
}
