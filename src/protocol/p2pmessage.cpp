#include "p2pmessage.h"

P2PMessage::P2PMessage(MESSAGE_TYPE type) : type_(type)
{

}

std::vector<unsigned char> P2PMessage::getValue()
{
    if(type_ == MESSAGE_TYPE::JOIN)
        return {'J','O','I','N','\n' };
    else
        return {'M','E','S','S','A','G','E','\n'};
}
