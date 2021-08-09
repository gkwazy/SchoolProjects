//
//  main.cpp
//  TalkingThroughPipes
//
//  Created by Garret Wasden on 2/21/21.
//

#include<cstdio>
#include<unistd.h>
#include<sys/wait.h>
#include<cstdlib>
#include"string"


int main(int argc, char * argv[]) {
    int fds[2];
    int results = pipe(fds);
    if (results < 0){
        fprintf(stderr, "pipe failed\n");
        exit(1);
    }
    
    int childNumber = fork();
    if (childNumber < 0){
        fprintf(stderr, "fork failed\n");
        exit(1);
    }else if (childNumber == 0){
//Child
        int messageLength;
        printf("I am the child fork\n");
        read(fds[0],&messageLength,1);
        char message[messageLength];
        read(fds[0],&message, messageLength);
        printf("received: %s", message);
        exit(0);
    }else{
//Parent
        std::string myInput = argv[1];
        int length = (int)myInput.length();
        write(fds[1], &length, 1);
        printf("sent length\n");
        write(fds[1], &myInput, length);
        printf("send message\n");
    }
    
    return 0;
}
