public class Main {
    public static void main(String[] args) {
        try {
            TrafficSim.runSim();
        } catch (DataValidationException | OrderNotFoundException e) {
            System.out.println("Unexpected exception occurred: " + e.getMessage());
            e.printStackTrace();
        }
    }
}