import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.net.Socket;
import java.util.HashMap;
import java.net.ServerSocket;

public class ChatServer {
    public static void main(String args[]) throws Exception {
        HashMap<String, DataOutputStream> client_map = new HashMap<>();
        int port = 6001;
        if(args.length == 1)
            port = Integer.parseInt(args[0]);
        ServerSocket server = new ServerSocket(port);
        while(true) {
            client_sock = server.accept();
            new ClientHandler(client_sock, client_map).start(); 
        }
    }
}

class ClientHandler extends Thread {
    // thread receives from client and sends to other clients
    String name;
    Socket client_sock;
    HashMap<String, DataOutputStream> client_map;
    ClientHandler(Socket client_sock, HashMap<String, DataOutputStream> client_map) {
        this.client_sock = client_sock;
        this.client_map = client_map;
    }
    public void run() {
        try {
        // get client name, add to map
        DataInputStream client_in = new DataInputStream(client_sock.getInputStream());
        DataOutputStream client_out = new DataOutputStream(client_sock.getOutputStream());
        name = client_in.readUTF();
        client_map.put(name, client_out);
        // forward client messages
        while(true) {
            String msg = client_in.readUTF();
            if(msg.equals("@request")) {
                String file_owner = client_in.readUTF();
                client_map.get(file_owner).writeUTF("@request");
                continue;
            }
            msg = name + ": " + msg;
            for(String other_client : client_map.keySet()) {
                if(other_client != name)
                    client_map.get(other_client).writeUTF(msg);
            }
        }
        } catch (Exception e) {
            client_map.remove(name);
            return;
        }
    }
}