#include <string>

template<typename Container, typename Predicat>
void erase_if(Container& container, Predicat predicat)
{
    auto it = container.cbegin();
    while(it != container.cend())
    {
        if(predicat(it->second))
            it = container.erase(it);
        else
            it++;
    }
}
