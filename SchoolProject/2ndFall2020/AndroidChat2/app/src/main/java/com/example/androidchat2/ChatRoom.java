package com.example.androidchat2;

import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;

import com.neovisionaries.ws.client.WebSocket;
import com.neovisionaries.ws.client.WebSocketAdapter;
import com.neovisionaries.ws.client.WebSocketFactory;

import org.json.JSONObject;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

public class ChatRoom extends AppCompatActivity {
    private RecyclerView mRecyclerView;
    private RecyclerView.Adapter mAdapter;
    private RecyclerView.LayoutManager mLayoutManager;
    private WebSocketFactory wsMaker;
    private WebSocket clientSocket;
    private String userName;
    private String room;
    private ArrayList<Message> chat;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_chat_room);
        // Get the Intent that started this activity and extract the string
        Intent intent = getIntent();
        String message = intent.getStringExtra(MainActivity.EXTRA_MESSAGE);
        String[] parseMessage = message.split(" ",2);
        userName = parseMessage[0];
        room = parseMessage[1];
        Log.d("test", parseMessage[1]);
        setTitle(parseMessage[1]);
        wsMaker = new WebSocketFactory();
        chat = new ArrayList<>();
        chat.add(new Message("hi", "testing"));
        chat.add(new Message("hi", "me"));
        chat.add(new Message("hi", "do"));
        mRecyclerView = findViewById(R.id.chatList);
        mRecyclerView.setHasFixedSize(false);
        mLayoutManager = new LinearLayoutManager(this);
        mAdapter = new MessageAdapter(chat);
        mRecyclerView.setLayoutManager(mLayoutManager);
        mRecyclerView.setAdapter(mAdapter);

        openSocket();
    }

    private void openSocket(){
        Log.d("test", "opened");
        try{
            clientSocket = wsMaker.createSocket("ws://10.0.2.2:8080");
            clientSocket.addListener(new WebSocketAdaptor(){
                @Override
                public void onTextMessage(WebSocket websocket, String text) throws Exception {
                    super.onTextMessage(websocket, text);
                    Log.d("test", text);
                    JSONObject json = new JSONObject(text);
                    Message message = new Message(json.getString("user"),
                            json.getString("message"));
                    Log.d("test", json.getString("user"));
                    Log.d("test", json.getString("message"));
                    runOnUiThread(() -> chat.add(message));
                }

                @Override
                public void onConnected(WebSocket websocket, Map<String, List<String>> headers)
                        throws Exception {
                    super.onConnected(websocket, headers);
                    String roomMessage = "join " + room;
                    clientSocket.sendText(roomMessage);

                }
            });
            clientSocket.connectAsynchronously();
        }catch(IOException e){
            e.printStackTrace();
        }
    }

    public void sendMessage(View view){
        EditText messageInput = (EditText) findViewById(R.id.messageInput);
        String message = userName + " " + messageInput.getText().toString();
        clientSocket.sendText(message);
        messageInput.setText("");
        Log.d("test", message);
    }

}