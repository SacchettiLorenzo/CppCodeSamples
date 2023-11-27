#include "common.h"

int common;
int private;
int received;

struct Client
{
    int pid;
    char username[USERNAMEMAXLEN];
};

struct Client client;
struct publicMsgBuf publicMsg;
struct privateMsgBuf privateMsgRcv;
struct privateMsgBuf privateMsgSend;
struct sigaction sa;

void handle_signal();
void boot(char *);
void connection();


int main(int argc, char *argv[])
{
    boot(argv[1]);
    connection();
    char* text = malloc(PRIVATEMSGLEN * sizeof(char));
    while (1)
    {
        fgets(text, PRIVATEMSGLEN, stdin);
        if (strlen(text) > 0)
        {
            sprintf(privateMsgSend.mtext,"%s %s %s %s %s","\033[31;1m",client.username,": ","\033[0m",text);
            msgsnd(private, &privateMsgSend, PRIVATEMSGLEN, 0);
            strcpy(privateMsgSend.mtext, "");
        }
        strcpy(text, "");
    }
}

void handle_signal()
{
    received = msgrcv(private, &privateMsgRcv, PRIVATEMSGLEN, privateMsgTypeClientRcv, 0);
    if (received >= 0)
    {
        printf("%s\n", privateMsgRcv.mtext);
    }
}

void boot(char *username)
{
    bzero(&sa, sizeof(sa));
    sa.sa_handler = handle_signal;
    sigaction(SIGUSR1, &sa, NULL);

    publicMsg.mtype = publicMsgType;
    privateMsgRcv.mtype = privateMsgTypeClientRcv;
    privateMsgSend.mtype = privateMsgTypeClientSend;

    strcpy(client.username, username);
}

void connection()
{

    sprintf(publicMsg.mtext, "%d", getpid());
    common = msgget(PUBLIC_KEY, IPC_CREAT | 0600);
    TEST_ERROR;
    msgsnd(common, &publicMsg, PUBLICMSGLEN, 0);
    private = msgget(getpid(), IPC_CREAT | 0600);
    /// TEST_ERROR;
}