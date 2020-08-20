#ifndef SENDDATA_H
#define SENDDATA_H


#include <QDataStream>
#include <QObject>
#include <QtNetwork>
#include <string>
#include <iostream>

template <typename T>
class SendData
{

    double timeStamp{0};
    T value{0};

public:
    SendData(T v, double tS)
    {
        timeStamp={tS};
        value={v};
    };
    SendData()
    {

    };


    //get
    double getTimeStamp() const
    {
        return timeStamp;
    };
    T getValue() const
    {
        return value;
    };

    //set
    void setTimeStamp(double a)
    {
        timeStamp = a;
    };
    void setValue(T a)
    {
        value = a;
    };

};

//overload of operators
//https://forum.qt.io/topic/87649/vector-struct-serialization-deserialization/7
//template<class TT>
//QDataStream &operator<<(QDataStream &stream, const std::vector<TT> &val)
//{
//    std::cout<<"Jestem w << vectora /n";
//    stream << static_cast<quint32>(val.size());
//    for(auto& singleVal : val)
//    stream << singleVal;
//    return stream;

//}


template<class TT>
QDataStream &operator>>(QDataStream &stream, std::vector<TT> &val)
{
    quint32 vecSize;
    val.clear();
    stream >> vecSize;
    val.reserve(vecSize);
    TT tempVal;
    while(vecSize--){
    stream >> tempVal;
    val.push_back(tempVal);
    }
    return stream;
}

//template<class TT>
//QDataStream &operator<<(QDataStream &stream, const SendData<TT> &val)
//{
//    std::cout<<"Jestem w << wartościach/n";
//  auto localValue = val.getValue();
//  auto localTimeStamp = val.getTimeStamp();
//  return stream << localValue <<localTimeStamp;
//}

template<class TT>
QDataStream &operator>>(QDataStream &stream, SendData<TT> &val)
{

    auto localValue = val.getValue();
    auto localTimeStamp = val.getTimeStamp();

    stream >> localValue >> localTimeStamp ;
    val.setValue(localValue);
    val.setTimeStamp(localTimeStamp);
    std::cout<<"Jestem w >> vectora /n";
    std::cout<<"Wartosc: "<<localValue<<std::endl;
    std::cout<<"Czas: "<<localTimeStamp<<std::endl;
    return stream;
}



#endif // SENDDATA_H
