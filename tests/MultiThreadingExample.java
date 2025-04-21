public class MultiThreadingExample {

    public static void main(String[] args) {
        // Создаем и запускаем первый поток
        Thread thread1 = new Thread(new RunnableTask("Поток 1"));
        thread1.start();

        // Создаем и запускаем второй поток
        Thread thread2 = new Thread(new RunnableTask("Поток 2"));
        thread2.start();

        // Главный поток также продолжает работать
        for (int i = 1; i <= 5; i++) {
            System.out.println("Главный поток: " + i);
            try {
                Thread.sleep(1000); // Пауза 1 секунда
            } catch (InterruptedException e) {
                System.out.println("Главный поток прерван");
            }
        }
    }

    // Статический вложенный класс, реализующий Runnable
    static class RunnableTask implements Runnable {
        private final String threadName;

        public RunnableTask(String threadName) {
            this.threadName = threadName;
        }

        @Override
        public void run() {
            for (int i = 1; i <= 5; i++) {
                System.out.println(threadName + ": " + i);
                try {
                    Thread.sleep(1000); // Пауза 1 секунда
                } catch (InterruptedException e) {
                    System.out.println(threadName + " прерван");
                }
            }
        }
    }
}