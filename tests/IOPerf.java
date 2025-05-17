import java.io.BufferedOutputStream;
import java.io.FileOutputStream;
import java.io.OutputStream;

public class IOPerf {
    public static void main(String ...args) {
        try (OutputStream outputStream = new FileOutputStream("aboba.txt")) {
            BufferedOutputStream bufferedOutputStream = new BufferedOutputStream(outputStream);
            String toWrite = "dfghjk\ndfghjk\ndfghj";
            bufferedOutputStream.write(toWrite.getBytes());
            bufferedOutputStream.flush();
        } catch (Exception e) {
            // TODO: handle exception
        }        
    }
}