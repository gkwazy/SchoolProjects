package com.example.chatandroid;

import androidx.appcompat.app.AppCompatActivity;

import android.app.ActionBar;
import android.content.Intent;
import android.os.Bundle;
import android.widget.LinearLayout;
import android.widget.ListView;
import android.widget.RelativeLayout;
import android.widget.TextView;

import java.util.ArrayList;

public class chatRoom extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_chat_room);

        Intent intent = getIntent();
        String info = intent.getStringExtra((MainActivity.EXTRA_MESSAGE));
        String[] arrayInfo = info.split(" ");
        setTitle("Room: "+arrayInfo[1]);
    }


    public void sendButton(){
//        LinearLayout linearLayout = (LinearLayout) findViewById(messages_view);
        TextView messageText = new TextView(this);
        ListView messageList = findViewById(R.id.messages_view);
        View message = MessageAdapter.getView()

    }

}