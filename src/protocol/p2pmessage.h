#ifndef P2PMESSAGE_H
#define P2PMESSAGE_H

#include <memory>
#include <vector>

class P2PMessage
{
public:
    enum class MESSAGE_TYPE { JOIN = 1, JOIN_RESPONSE = 2, LEAVE = 5, LEAVE_RESPONSE = 6 };
    P2PMessage(MESSAGE_TYPE type);

    static std::unique_ptr<P2PMessage> createJoinMessage()
    {
        return std::make_unique<P2PMessage>(P2PMessage::MESSAGE_TYPE::JOIN);
    }

    static std::unique_ptr<P2PMessage> createJoinResponseMessage()
    {
        return std::make_unique<P2PMessage>(P2PMessage::MESSAGE_TYPE::JOIN_RESPONSE);
    }

    MESSAGE_TYPE getType() const { return type_; }
    std::vector<unsigned char> getValue();
private:
    MESSAGE_TYPE type_;
};

#endif // P2PMESSAGE_H
