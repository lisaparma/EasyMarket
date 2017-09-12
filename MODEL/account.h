#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QString>

class account
{
private:
    QString username;
    QString password;
protected:
    account(QString, QString);
public:
    QString getUsername() const;
    QString getPassword() const;

    virtual float soldiSpesa() const = 0;
};


#endif // ACCOUNT_H
