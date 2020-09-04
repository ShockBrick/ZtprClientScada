#ifndef SENDDATA_H
#define SENDDATA_H


#include <QDataStream>
#include <QObject>
#include <QtNetwork>
#include <string>
#include <iostream>
/** Szablon klasy. Klasa ta służy do przechowywania próbki danych.**/
template <typename T>
class SendData
{
    double timeStamp{0};/**< \brief Zmienna timeStamp oznacza czas pobrania próbki..*/
    T value{0};/**< \brief Zmienna value oznacza wartość danej próbki.*/

public:
    /** \brief Konstruktor wpisujący w pola timeStamp i value argumenty funkcji.
     *@param v Jest zapisywany do zmiennej value.
     *@param tS Jest zapisywany do zmiennej timeStamp.
     */
    SendData(T v, double tS)
    {
        timeStamp={tS};
        value={v};
    };
    SendData()
    {

    };

    /** \brief Funkcja zwraca wartość zmiennej timeStamp.
     *
     */
    double getTimeStamp() const
    {
        return timeStamp;
    };
    /** \brief Funkcja zwraca wartość zmiennej value.
     *
     */
    T getValue() const
    {
        return value;
    };

    /** \brief Funkcja ustawia wartość zmiennej timeStamp.
     * @param a Zmienna timeStamp=a
     */
    void setTimeStamp(double a)
    {
        timeStamp = a;
    };
    /** \brief Funkcja ustawia wartość zmiennej value.
     * @param a Zmienna value=a
     */
    void setValue(T a)
    {
        value = a;
    };

};

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

template<class TT>
QDataStream &operator>>(QDataStream &stream, SendData<TT> &val)
{

    auto localValue = val.getValue();
    auto localTimeStamp = val.getTimeStamp();

    stream >> localValue >> localTimeStamp ;
    val.setValue(localValue);
    val.setTimeStamp(localTimeStamp);
    return stream;
}
#endif // SENDDATA_H
