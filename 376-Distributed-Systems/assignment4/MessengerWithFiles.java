/* 
    java Messenger -l 6001
    java Messenger -l 6002 -p 6001
    py test1-messenger-with-files-java.py
    py test2-messenger-with-files-java.py
*/

import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.InputStreamReader;
import java.net.ServerSocket;
import java.net.Socket;

public class MessengerWithFiles {
    public static void main(String args[]) throws Exception {
        // Create server or client socket
        int listening_port = 6001;
        int server_port = 6002;
        int transfer_port = 6002;
        Socket client_sock;
        String server_addr = "localhost";
        boolean isServer = true;
        for(int i=0; i<args.length; i++) {
            switch(args[i]) {
                case "-l":
                    listening_port = Integer.parseInt(args[i+=1]); 
                    break;
                case "-p":
                    server_port = Integer.parseInt(args[i+=1]);
                    isServer = false;
                    break;
                case "-s":
                    server_addr = args[i+=1];
                    break;
            }
        }
        if(isServer == true) {
            ServerSocket server = new ServerSocket(listening_port);
            client_sock = server.accept();
            server.close();
        }
        else { 
            // connect to server and set up transfer socket
            transfer_port = listening_port;
            client_sock = new Socket(server_addr, server_port);
        }
        DataInputStream client_in = new DataInputStream(client_sock.getInputStream());
        DataOutputStream client_out = new DataOutputStream(client_sock.getOutputStream());
        // Give transfer port to server
        if(isServer == true)
            transfer_port = client_in.readInt();
        else  
            client_out.writeInt(transfer_port);
        // Start receiver thread
        new Receiver(client_in, transfer_port).start();
        BufferedReader reader = new BufferedReader( 
			new InputStreamReader(System.in) );
        // Interact with UI
        while(true) {
            try {
                System.out.println("Enter an option ('m', 'f', 'x'):\n  (M)essage (send)\n  (F)ile (request)\n  e(X)it");
                switch(reader.readLine()) {
                    case "m":
                    // sends a message
                        System.out.println("Enter your message: ");
                        client_out.writeUTF(reader.readLine());
                        break;
                    case "f":
                    // requests file 
                        System.out.println("Which file do you want?");
                        String file_name = reader.readLine();
                        new RequestFile(transfer_port, file_name).start();
                        client_out.writeUTF("@request");
                        break;
                    case "x":
                    // exits program
                        System.out.println("closing sockets...goodbye");
                        System.exit(0);
                        break;
                    default:
                        break;
                }
            } catch (Exception e) {
                System.exit(0);
            }
        }
    }
}

class Receiver extends Thread {
    DataInputStream client_in;
    int transfer_port;
    Receiver(DataInputStream client_in, int transfer_port) {
        this.client_in = client_in;
        this.transfer_port = transfer_port;
    }
    public void run() {
        while(true) {
            try {
                String msg = client_in.readUTF();
                if(msg.equals("@request")) {
                    new SendFile(transfer_port).start();
                    continue;
                }
                System.out.println(msg);
            } catch (Exception e) {
                System.exit(0);
            }
        }
    }
}

class RequestFile extends Thread {
    Socket transfer_sock;
    int transfer_port;
    String file_name;
    RequestFile(int transfer_port, String file_name) {
        this.transfer_port = transfer_port;
        this.file_name = file_name;
    }
    public void run() {
        try {
            ServerSocket transfer_server = new ServerSocket(transfer_port);
            transfer_sock = transfer_server.accept();
            transfer_server.close();
            DataInputStream input = new DataInputStream(transfer_sock.getInputStream());
            DataOutputStream output = new DataOutputStream(transfer_sock.getOutputStream());
            output.writeUTF(file_name);
            FileOutputStream file_output = new FileOutputStream(file_name);
            byte[] file_buf = new byte[1500];
            int bytes_read;
            while((bytes_read = input.read(file_buf)) != -1)
                file_output.write(file_buf, 0, bytes_read);
            file_output.close();
            transfer_sock.close();
        } catch (Exception e) {
            try {
                transfer_sock.close();
            } catch (Exception e2) {}
        }
    }
}

class SendFile extends Thread {
    int transfer_port;
    Socket transfer_sock;
    SendFile(int transfer_port) {
        this.transfer_port = transfer_port;
    }
    public void run() {
        try {
            transfer_sock = new Socket("localhost", transfer_port);
            DataInputStream input = new DataInputStream(transfer_sock.getInputStream());
            DataOutputStream output = new DataOutputStream(transfer_sock.getOutputStream());
            String file_name = input.readUTF();
            System.out.println("filename is "+file_name);
            FileInputStream file_input = new FileInputStream(file_name);
            byte[] file_buf = new byte[1500];
            int bytes_read;
            while((bytes_read = file_input.read(file_buf)) != -1)
                output.write(file_buf, 0, bytes_read);
            file_input.close();
        } catch (Exception e) {
            try {
                transfer_sock.close();
            } catch (Exception e2) {}
        }
    }
}