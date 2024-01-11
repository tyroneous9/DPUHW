/* 
    java Messenger -l 6001
    java Messenger 6001 localhost
*/

import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.InputStreamReader;
import java.net.ServerSocket;
import java.net.Socket;

public class Messenger {
    public static void main(String args[]) throws Exception {
        // Create server or client socket
        Socket client_sock;
        if(args[0].equals("-l")) {
            ServerSocket server = new ServerSocket(Integer.parseInt(args[1]));
            client_sock = server.accept();
            server.close();
        }
        else
            client_sock = new Socket("localhost", Integer.parseInt(args[0]));
        DataInputStream client_in = new DataInputStream(client_sock.getInputStream());
        DataOutputStream client_out = new DataOutputStream(client_sock.getOutputStream());
        // Start receiver thread
        new Receiver(client_in).start();
        BufferedReader reader = new BufferedReader( 
			new InputStreamReader(System.in) );
        // Send messages thru standard input
        while(true) {
            try {
                String msg = reader.readLine();
                client_out.writeUTF(msg);
            } catch (Exception e) {
                client_sock.close();
                System.exit(0);
            }
        }
    }
}

class Receiver extends Thread {
    DataInputStream client_in;
    Receiver(DataInputStream client_in) {
        this.client_in = client_in;
    }
    public void run() {
        while(true) {
            try {
                String msg = client_in.readUTF();
                System.out.println(msg);
            } catch (Exception e) {
                System.exit(0);
            }
        }
    }
}

