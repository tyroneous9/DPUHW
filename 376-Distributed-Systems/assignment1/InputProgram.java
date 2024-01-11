import java.io.BufferedReader;
import java.io.InputStreamReader;

public class InputProgram {
    public static void main(String args[]) {
        // read command line
        String[] options_list = new String[3];
        for(int i=0; i<args.length; i++) {
            if(args[i].charAt(0) == '-') {
                switch(args[i].charAt(1)) {
                    case 'o': 
                        options_list[0] = args[i+=1];
                        break;
                    case 't':
                        options_list[1] = args[i+=1];
                        break;
                    case 'h':
                        options_list[2] = "1";
                        break;
                }
            }
        }
        // read standard input
        System.out.println("Standard Input: ");
        BufferedReader input = new BufferedReader(
            new InputStreamReader(System.in)    );
        String line;
        try {
            while((line = input.readLine()) != null) {
                System.out.println(line);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

        // print command line args
        System.out.println("Command line arguments: ");
        for(int i=0; i<options_list.length; i++) {
            if(options_list[i] != null) {
                String format = "option "+(i+1)+": "+options_list[i];
                if(i==2)
                    format = "option "+(i+1);
                System.out.println(format);
            }
        }
    }
}