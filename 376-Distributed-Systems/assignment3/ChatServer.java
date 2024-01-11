import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.net.Socket;
import java.net.ServerSocket;

public class ChatServer {
    public static void main(String args[]) throws Exception {
        final int MAX_CLIENT_NUM = 10;
        DataOutputStream[] clientList = new DataOutputStream[MAX_CLIENT_NUM];
        int port = 6001;
        if(args.length == 1)
            port = Integer.parseInt(args[0]);
        ServerSocket server = new ServerSocket(port);
        int clientNum=0;
        while(true) {
            Socket client_sock = server.accept();
            // find next empty spot for client
            while(clientList[clientNum] != null) {
                clientNum++;
                if(clientNum > MAX_CLIENT_NUM)
                    clientNum = 0;
            }
            clientList[clientNum] = new DataOutputStream(client_sock.getOutputStream());
            // let a thread handle the new client
            new clientHandler(client_sock, clientList, clientNum).start(); 
        }
    }
}

class clientHandler extends Thread {
    // thread receives from client and sends to other clients
    Socket client_sock;
    DataOutputStream[] clientList;
    int clientNum;
    clientHandler(Socket client_sock, DataOutputStream[] clientList, int clientNum) {
        this.client_sock = client_sock;
        this.clientList = clientList;
        this.clientNum = clientNum;
    }
    public void run() {
        try {
        // get client name
        DataInputStream client_in = new DataInputStream(client_sock.getInputStream());
        String name = client_in.readUTF();
        // forward client messages
        while(true) {
            String msg = name + ": " + client_in.readUTF();
            int i=0;
            for(DataOutputStream other_client : clientList) {
                if(i != clientNum && other_client != null)
                    other_client.writeUTF(msg);
                i++;
            }
        }
        } catch (Exception e) {
            clientList[clientNum] = null;
            return;
        }
    }
}