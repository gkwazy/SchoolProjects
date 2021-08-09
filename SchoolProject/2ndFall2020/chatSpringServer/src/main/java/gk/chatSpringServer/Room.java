package gk.chatSpringServer;

import org.springframework.web.socket.TextMessage;
import org.springframework.web.socket.WebSocketMessage;
import org.springframework.web.socket.WebSocketSession;

import java.io.IOException;
import java.util.ArrayList;

public class Room {
    String name;
    public static ArrayList<WebSocketSession> clients = new ArrayList<WebSocketSession>();

    public Room(String name, WebSocketSession client){
        this.name = name;
        clients.add(client);
    }
    public static boolean findRoom(WebSocketSession client) {
       return clients.contains(client);

    }

    public void addClient(WebSocketSession client) {
        clients.add(client);
    }

    public boolean clientInRoom(WebSocketSession client) {
       return clients.contains(client);
    }

    public void forwardMessage(TextMessage message) throws IOException {
        System.out.println(clients.size());
        String [] parseMessage = message.getPayload().split(" ",2);
        TextMessage newMessage;
        String json = "{\"user\" : \""+ parseMessage[0] + "\", \"message\": \""
                + parseMessage[1]+ "\"}" ;
        newMessage = new TextMessage(json);
        for (WebSocketSession client: clients) {
            client.sendMessage(newMessage);
        }
    }
}
