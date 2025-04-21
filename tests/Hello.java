public class Hello {

    @DllImport("libc")
    static native int write(int fd, @InOut byte[] data, int length);

    @DllImport("libc")
    static native int read(int fd, @InOut byte[] data, int length);

    public static void main(String args[]) {
        System.out.println("Hello world!");
    }
}