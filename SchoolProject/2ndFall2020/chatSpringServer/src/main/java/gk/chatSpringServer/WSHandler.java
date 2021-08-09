package gk.chatSpringServer;

import netscape.javascript.JSObject;
import org.springframework.web.socket.TextMessage;
import org.springframework.web.socket.WebSocketMessage;
import org.springframework.web.socket.WebSocketSession;
import org.springframework.web.socket.handler.TextWebSocketHandler;

import java.io.IOException;
import java.util.ArrayList;

public class WSHandler extends TextWebSocketHandler {
    ArrayList<Room> rooms = new ArrayList<Room>();
    @Override
    public void handleTextMessage(WebSocketSession client, TextMessage message) throws IOException {
//        Room room = Room.findRoom(client);
        System.out.println("connecting");
        String [] parseMessage = message.getPayload().split(" ",2);
        boolean found = false;
        System.out.println(parseMessage[0]);
        System.out.println(parseMessage[0].equals("join"));
        if (parseMessage[0].equals("join")) {
            System.out.println("joinning");
            for (Room room: rooms) {
                System.out.println(room.name);
                if (room.name.equals(parseMessage[1])) {
                    System.out.println("room found");
                    room.addClient(client);

                    found = true;
                }
            }
            if (found == false) {
                System.out.println("making new room");
                Room newRoom = new Room(parseMessage[1], client);
                rooms.add(newRoom);
            }
                TextMessage newMessage;
                String json = "{\"user\" : \"" + parseMessage[0] + "\", \"message\": \""
                        + parseMessage[1] + "\"}";
                newMessage = new TextMessage(json);
                client.sendMessage(newMessage);

        }else{
            for (Room room: rooms) {
                if(room.clientInRoom(client))
                    System.out.println("send message");
                    room.forwardMessage(message);
            }


            }
        }
    }


//