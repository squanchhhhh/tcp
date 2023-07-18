#include <cstdint>
#include <iostream>
#include <vector>
struct TcpHeader {
    uint16_t sourcePort;
    uint16_t destPort;
    uint32_t sequenceNumber;
    uint32_t acknowledgementNumber;
    uint16_t dataOffsetAndReservedAndFlags;
    uint16_t windowSize;
    uint16_t checksum;
    uint16_t urgentPointer;
};
class Tcp{
public:
    TcpHeader* header;
    std::vector<uint8_t> *tcpMessage;
//构造tcp头部
    void creatHead(uint16_t sourcePort,
    uint16_t destPort,
    uint32_t sequenceNumber,
    uint32_t acknowledgementNumber,
    uint16_t dataOffsetAndReservedAndFlags,
    uint16_t windowSize,
    uint16_t checksum,
    uint16_t urgentPointer){
            this->header->sourcePort=sourcePort;
            this->header->destPort=destPort;
            this->header->sequenceNumber=sequenceNumber;
            this->header->acknowledgementNumber = acknowledgementNumber;
        this->header->dataOffsetAndReservedAndFlags=dataOffsetAndReservedAndFlags;
            this->header->windowSize=windowSize;
            this->header->checksum=checksum;
            this->header->urgentPointer=urgentPointer;
    }
//在头部后面加入message，并且更改头部的checksum和offset
    void addMessage(char* message,int length){
        //求出数据和首部的总长度，单位为4字节
        auto len = uint16_t(5+length/4);
        len = len<<12;
        //更新tcp长度,将dataOffset的前4位设置为len的后4位
        this->header->dataOffsetAndReservedAndFlags&=0x0fff;
        this->header->dataOffsetAndReservedAndFlags|=len;
        //更新checksum，这里需要用到ip层的数据，暂时跳过
        this->header->checksum = this->header->checksum;
        //将message加入到头部后面，形成tcp数据包
        tcpMessage = new std::vector<uint8_t>(20 + length);
        // 将TCP头部复制到字节序列中
        std::memcpy(tcpMessage->data(), this->header, 20);
        // 将消息数据复制到字节序列中
        std::memcpy(tcpMessage->data() + 20, message, length);
    }
    //解码tcp信息
    void decode(){
       uint16_t sourcePort;
       uint16_t destPort;
       uint32_t sequenceNumber;
       uint32_t acknowledgementNumber;
       uint16_t dataOffsetAndReservedAndFlags;
       uint16_t windowSize;
       uint16_t checksum;
       uint16_t urgentPointer;
       std::memcpy(&sourcePort,tcpMessage->data(),2);
       std::memcpy(&destPort,tcpMessage->data()+2,2);
       std::memcpy(&sequenceNumber,tcpMessage->data()+4,4);
       std::memcpy(&acknowledgementNumber,tcpMessage->data()+8,4);
       std::memcpy(&dataOffsetAndReservedAndFlags,tcpMessage->data()+12,2);
       std::memcpy(&windowSize,tcpMessage->data()+14,2);
       std::memcpy(&checksum,tcpMessage->data()+16,2);
       std::memcpy(&urgentPointer,tcpMessage->data()+18,2);
       char dataOffset = (char)(dataOffsetAndReservedAndFlags>>12);
       uint8_t reverse = ((uint8_t)(dataOffsetAndReservedAndFlags>>6))&0x3F;
       uint8_t flags = ((uint8_t)(dataOffsetAndReservedAndFlags>>6))&0x3F;
       bool URG,ACK,PSH,RST,SYN,FIN;
       URG = flags>=32;
       ACK = flags>=16&&flags<32;
       PSH = flags>=8&&flags<16;
       RST = flags>=4&&flags<8;
       SYN = flags>=2&&flags<4;
       FIN = flags>=1&&flags<2;
       std::cout<<"解码成功"<<std::endl;
       std::cout<<"原端口为:"<<(int)sourcePort<<std::endl;
       std::cout<<"目的端口为:"<<(int)destPort<<std::endl;
       std::cout<<"序列号为:"<<(int)sequenceNumber<<std::endl;
       std::cout<<"确认号为:"<<(int)acknowledgementNumber<<std::endl;
       std::cout<<"长度为:"<<(int)dataOffset<<std::endl;
       std::cout<<"保留号为:"<<(int)reverse<<std::endl;
       std::cout<<"URG为:"<<URG<<std::endl;
       std::cout<<"ACK为:"<<ACK<<std::endl;
       std::cout<<"PSH为:"<<PSH<<std::endl;
       std::cout<<"RST为:"<<RST<<std::endl;
       std::cout<<"SYN为:"<<SYN<<std::endl;
       std::cout<<"FIN为:"<<FIN<<std::endl;
       std::cout<<"窗口为:"<<(int)windowSize<<std::endl;
       std::cout<<"校验和为:"<<(int)checksum<<std::endl;
       std::cout<<"紧急指针为:"<<(int)urgentPointer<<std::endl;
    }
    Tcp(){
        this->header = new TcpHeader;
    }
};
class Client{
public:
    uint16_t port;
    void firstConnect(uint16_t destPort,
                      uint16_t dataOffsetAndReservedAndFlags,
                      uint16_t windowSize,
                      uint16_t checksum,
                      uint16_t urgentPointer){
        uint16_t sequenceNumber = 1000;
        uint16_t acknowledgementNumber = 0;
        auto tcp = new Tcp;
        tcp->creatHead(this->port,destPort,sequenceNumber,acknowledgementNumber,dataOffsetAndReservedAndFlags,windowSize,checksum,urgentPointer);
    }
};
class server{
public:
    int type;
    void getFirstAndReturnSecond(){

    }
};
int main(){

};
