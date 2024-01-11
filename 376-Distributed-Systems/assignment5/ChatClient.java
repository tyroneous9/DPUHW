// py autograde-chat-with-files-java.py

import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.InputStreamReader;
import java.net.ServerSocket;
import java.net.Socket;


public class ChatClient {
    public static void main(String args[]) throws Exception {
        int server_port = 6001;
        int transfer_port = 6002;
        boolean send_port = false;
        for(int i=0; i<args.length; i++) {
            switch(args[i]) {
                case "-l":
                    transfer_port = Integer.parseInt(args[i+=1]); 
                    send_port = true;
                    break;
                case "-p":
                    server_port = Integer.parseInt(args[i+=1]);
                    break;
                default:
                    break;
            }
        }
        Socket client_sock = new Socket("localhost", server_port);
        DataInputStream client_in = new DataInputStream(client_sock.getInputStream());
        DataOutputStream client_out = new DataOutputStream(client_sock.getOutputStream());
        if(send_port)
            client_out.writeInt(transfer_port);
        // receiver thread
        new Receiver(client_in, transfer_port).start();
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        try {
            System.out.println("What is your name?");
            client_out.writeUTF(reader.readLine());
            while(true) {
                System.out.println("Enter an option ('m', 'f', 'x'):\n  (M)essage (send)\n  (F)ile (request)\n  e(X)it");
                switch(reader.readLine()) {
                    case "m":
                    // sends a message
                        System.out.println("Enter your message: ");
                        client_out.writeUTF(reader.readLine());
                        break;
                    case "f":
                    // requests file 
                        System.out.println("Who owns the file?");
                        String file_owner = reader.readLine();
                        System.out.println("Which file do you want?");
                        String file_name = reader.readLine();
                        new TransferHandler(file_name, transfer_port).start();
                        client_out.writeUTF("@request");
                        client_out.writeUTF(file_owner);
                        break;
                    case "x":
                    // exits program
                        System.out.println("closing sockets...goodbye");
                        System.exit(0);
                        break;
                    default:
                        break;
                    }
            }
        } catch (Exception e) {
            System.exit(0);
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
                if(msg.equals("@request"))
                    new TransferHandler(transfer_port).start();
                else
                    System.out.println(msg);
            } catch (Exception e) {
                System.exit(0);
            }
        }
    }
}

class TransferHandler extends Thread {
    Socket transfer_sock;
    String file_name;
    int transfer_port;
    boolean is_requester = false;
    boolean serverStarted = false;
    TransferHandler(String file_name, int transfer_port) {
        this.file_name = file_name;
        this.transfer_port = transfer_port;
        is_requester = true;
    }
    TransferHandler(int transfer_port) {
        this.transfer_port = transfer_port;
    }
    public void run() {
        if(is_requester == true) 
            request();
        else
            send();
    }

    public void request() {
        synchronized(this) {
            try {
                ServerSocket transfer_server = new ServerSocket(transfer_port);
                serverStarted = true;
                notify();
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
                    File file = new File(file_name);
                    file.delete();
                    transfer_sock.close();
                } catch (Exception e2) {return;}
            }
        }
    }

    public void send() {
        synchronized(this) {
            try {
                while(!serverStarted) {
                    wait();
                }
                Thread.sleep(5000);
                transfer_sock = new Socket("localhost", transfer_port);
                DataInputStream input = new DataInputStream(transfer_sock.getInputStream());
                DataOutputStream output = new DataOutputStream(transfer_sock.getOutputStream());
                String file_name = input.readUTF();
                File file = new File(file_name);
                if ( !file.exists() || !file.canRead() ) {
                    System.out.println(file_name+" was not found");
                    transfer_sock.close();
                }
                FileInputStream file_input = new FileInputStream(file);
                byte[] file_buf = new byte[1500];
                int bytes_read;
                while((bytes_read = file_input.read(file_buf)) != -1)
                    output.write(file_buf, 0, bytes_read);
                file_input.close();
            } catch (Exception e) {
                try {
                    transfer_sock.close();
                } catch (Exception e2) {return;}
            }
        }
    }
}



