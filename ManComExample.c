#include <windows.h>

#include <stdio.h>
#include <ManCom.h>

void MyAccept(const ManComAcceptor* acceptor)
{
    printf("MyAccept for %s\n", acceptor->name);
}

char BadChannelNameExample()
{
    ManComResult result;
    ManComAcceptor acceptor;
    
    ZeroMemory(&acceptor, sizeof(acceptor));
    acceptor.name = "BadChannelName";
    acceptor.accept = MyAccept;

    result = ManComStartAcceptor(&acceptor);
    if(result == MAN_COM_RESULT_BAD_CHANNEL_NAME)
    {
        printf("[BadChannelNameExample] ManComStartAcceptor failed expectedly with '%s'\n", ManComResultString(result));
        return 0; // Success
    }
    printf("[BadChannelNameExample] Error: expected ManComStartAcceptor to return %s but returned %s\n",
        ManComResultString(MAN_COM_RESULT_BAD_CHANNEL_NAME), ManComResultString(result));
    return 1; // Fail
}

char AcceptorExample()
{
    ManComResult result;
    ManComAcceptor acceptor;

    ZeroMemory(&acceptor, sizeof(acceptor));
    acceptor.name = "ExampleChannel";
    acceptor.accept = MyAccept;

    result = ManComStartAcceptor(&acceptor);
    if(result != MAN_COM_RESULT_OK)
    {
        printf("ManComStartAcceptor failed: %s\n", ManComResultString(result));
        return 1; // Fail
    }

    /*
    while(1)
    {
        status = ManComWait();
        if(status == CRITICAL_ERROR)
        {
            // Handle Error
        }
    }
    */
    return 0;
}

int main(int argc, const char* argv[])
{
    BadChannelNameExample();
    AcceptorExample();
    return 0;
}