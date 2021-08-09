package gk.company;

import java.net.Socket;
import java.util.ArrayList;

public class Room {
    String name;
    ArrayList<Socket> clients = new ArrayList<Socket>();;
    ArrayList <UserMessage> messageHistory = new ArrayList<UserMessage>();

    public Room(String name) {
        this.name = name;
    }

    public void addSocket(Socket client) {
        clients.add(client);
    }


    public void addMessage(UserMessage message){
        messageHistory.add(message);
    }
    //array of users
    //user stuff
    //echo
}
