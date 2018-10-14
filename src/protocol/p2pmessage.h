#ifndef P2PMESSAGE_H
#define P2PMESSAGE_H


class P2PMessage
{
public:
    enum class MESSAGE_TYPE { JOIN, JOIN_RESPONSE, LEAVE, LEAVE_RESPONSE };
    P2PMessage(MESSAGE_TYPE type);
private:
    MESSAGE_TYPE type_;
};

#endif // P2PMESSAGE_H
