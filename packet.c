#include "packet.h"


/* Pacote a ser enviado para o cliente ! */
u8 serverPacket[50];
int packet_count = 0; // contador dos pacotes

void clearPacket() {
    memset(serverPacket, 0x0, 50);
    packet_count = 0;
}

void writeByte(u8 b) {
    serverPacket[packet_count] = b;
    packet_count++;
}

void writeShort(u16 s) {
    memcpy(serverPacket + packet_count, &s, 2);
    packet_count += 2;
}

void writeInt(u32 i) {
    memcpy(serverPacket + packet_count, &i, 4);
    packet_count += 4;
}

void writeHeader_1(u32 HEADER) {
    memcpy(serverPacket, &HEADER, sizeof(HEADER));
    packet_count += 4;
}

void writeHeader_2(u32 HEADER) {
    memcpy(serverPacket + 4, &HEADER, sizeof(HEADER));
    packet_count += 4;
}

void writeChecksum() {

}

u32 readInt() {
    u32 packet = serverPacket[packet_count];
    packet_count++;
    packet = ((serverPacket[packet_count] << 8)  | packet);
    packet_count++;
    packet = ((serverPacket[packet_count] << 16) | packet);
    packet_count++;
    packet = ((serverPacket[packet_count] << 24) | packet);
    packet_count++;
    return packet;
}

u16 readShort() {
    u16 packet = serverPacket[packet_count];
    packet_count++;
    packet = ((serverPacket[packet_count] << 8)  | packet);
    packet_count++;
    return packet;
}

u8  readByte() {
    u8 packet = serverPacket[packet_count];
    packet_count++;
    return packet;
}


/* Pacotes do Cliente */
void packet_Login() {
    /* Onde o nosso login fica salvo ! */
    char superuser[20];
    /* Limpa a string do login ! */
    memset(superuser, 0, 20);

    printf("Digite a senha do super-user:\n");
    scanf("%s", &superuser);

    /* Pacote com o login do cliente, lembre-se que isso é para super user ! */
    writeInt(CLIENT_PACKET_UNK); // Pacote desconhecido, pode ser um head
    writeInt(CLIENT_PACKET_LOGIN_SEND); // Provavelmente o header para Login
    writeByte(0x09);
    writeShort(0x0DBF);
    writeInt(0x65747365);
    writeByte(0x74);
    writeShort(0x0A0D); // Desconhecido
    writeByte(0x1C); // Checksum ?   /*VERIFICAR CODIGO DO CHECKSUM NO JAVA*/ 


}

/* Cliente Handle, todos os pacotes são *decodificados* nessa rotina */

void packetHandle() {
    u32 HEADER_1 = readInt();
    u32 HEADER_2 = readInt();

    switch (HEADER_1) {
        

        default:
            printf("Packet Invalido ou nao implementado: 0x%X\n", HEADER_1);
        break;
    }
}
