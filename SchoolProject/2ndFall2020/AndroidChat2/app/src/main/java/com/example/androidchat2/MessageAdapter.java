package com.example.androidchat2;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import java.util.ArrayList;

public class MessageAdapter extends RecyclerView.Adapter<MessageAdapter.MessageViewHolder> {
    private ArrayList<Message> chat;

    public static class MessageViewHolder extends RecyclerView.ViewHolder{
        public TextView userView;
        public TextView messageView;


        public MessageViewHolder(@NonNull View itemView) {
            super(itemView);
            userView = itemView.findViewById(R.id.userView);
            messageView = itemView.findViewById(R.id.messageView);
        }
    }

public MessageAdapter( ArrayList<Message> chat){
        this.chat = chat;
}

    @NonNull
    @Override
    public MessageViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        View v = LayoutInflater.from(parent.getContext()).inflate(R.layout.message, parent,
                false);
        MessageViewHolder mvh = new MessageViewHolder(v);
        return mvh;
    }

    @Override
    public void onBindViewHolder(@NonNull MessageViewHolder holder, int position) {
        Message currentMessage = chat.get(position);
        holder.userView.setText(currentMessage.getUserView());
        holder.messageView.setText((currentMessage.getMessageView()));
    }

    @Override
    public int getItemCount() {
        return chat.size();
    }
}
