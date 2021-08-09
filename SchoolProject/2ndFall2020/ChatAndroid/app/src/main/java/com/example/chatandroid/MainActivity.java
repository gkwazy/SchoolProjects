package com.example.chatandroid;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;

public class MainActivity extends AppCompatActivity {
    public static final String EXTRA_MESSAGE = "com.example.myfirstapp.MESSAGE";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    public void enterRoom(View view) {
        Intent intent = new Intent(this, chatRoom.class);
        EditText userNames = (EditText) findViewById(R.id.userNameWanted);
        EditText roomWanted = (EditText) findViewById(R.id.roomWanted);
        String infoNeeded = userNames.getText().toString() + " "
                + roomWanted.getText().toString();
        intent.putExtra(EXTRA_MESSAGE, infoNeeded);
        startActivity(intent);

    }
}