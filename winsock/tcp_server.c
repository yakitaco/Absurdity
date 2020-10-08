#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#define BUFFER_SIZE 256

int
main() {
    /* �|�[�g�ԍ��A�\�P�b�g */
    unsigned short port = 9876;
    int srcSocket;  // ����
    int dstSocket;  // ����

    /* sockaddr_in �\���� */
    struct sockaddr_in srcAddr;
    struct sockaddr_in dstAddr;
    int dstAddrSize = sizeof(dstAddr);

    /* �e��p�����[�^ */
    int numrcv;
    char buffer[BUFFER_SIZE];

    /************************************************************/
    /* Windows �Ǝ��̐ݒ� */
    WSADATA data;
    WSAStartup(MAKEWORD(2, 0), &data);

    /* sockaddr_in �\���̂̃Z�b�g */
    memset(&srcAddr, 0, sizeof(srcAddr));
    srcAddr.sin_port = htons(port);
    srcAddr.sin_family = AF_INET;
    srcAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    /* �\�P�b�g�̐��� */
    srcSocket = socket(AF_INET, SOCK_STREAM, 0);

    /* �\�P�b�g�̃o�C���h */
    bind(srcSocket, (struct sockaddr*)&srcAddr, sizeof(srcAddr));

    /* �ڑ��̋��� */
    listen(srcSocket, 1);

    /* �ڑ��̎�t�� */
    printf("Waiting for connection ...\n");
    dstSocket = accept(srcSocket, (struct sockaddr*)&dstAddr, &dstAddrSize);
    printf("Connected from %s\n", inet_ntoa(dstAddr.sin_addr));

    /* �p�P�b�g��M */
    while (1) {
        numrcv = recv(dstSocket, buffer, BUFFER_SIZE, 0);
        if (numrcv == 0 || numrcv == -1) {
            status = closesocket(dstSocket); break;
        }
        printf("received: %s\n", buffer);
    }

    /* Windows �Ǝ��̐ݒ� */
    WSACleanup();
}