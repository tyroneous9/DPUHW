import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.InputStreamReader;
import java.net.Socket;


public class ChatClient {
    public static void main(String args[]) throws Exception {
        int port = 6001;
        if(args.length == 1)
            port = Integer.parseInt(args[0]);
        Socket client_sock = new Socket("localhost", port);
        DataInputStream client_in = new DataInputStream(client_sock.getInputStream());
        DataOutputStream client_out = new DataOutputStream(client_sock.getOutputStream());
        // send msgs
        Sender send = new Sender(client_sock, client_out);
        send.start();
        // receive msgs
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

class Sender extends Thread {
    Socket client_sock;
    DataOutputStream client_out;
    Sender(Socket client_sock, DataOutputStream client_out) {
        this.client_sock = client_sock;
        this.client_out = client_out;
    }

    public void run() {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        while(true) {
            try {
                String msg = reader.readLine();
                client_out.writeUTF(msg);
            } catch (Exception e) {
                System.exit(0);
            }
        }
    }
}